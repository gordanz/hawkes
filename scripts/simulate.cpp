#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <iomanip>
#include <ctime>
#include <cmath>

#include <Rcpp.h>

#include "include/pcg_random.hpp"

#define MAXPOIS 20

using namespace std;

typedef pcg32 rng_type;

void progress_bar(size_t i, size_t maxi)
{
    static int display_next = 0;
    int percent = (int)(100 * i ) / maxi;
    if (percent >= display_next)
    {
        cout << "\r" << "Simulating ["
             << string(percent / 5, (char)43u)
             << string(100 / 5 - percent / 5, ' ') << "] ";
        cout << percent << "% ";
        cout.flush();
        display_next += 1;
    };
};


class Parameters
{
public:
    double mu;
    double oomu;
    double a;
    vector<double> pois_prob;
    size_t max_pois;
    double alpha;
    double min_pareto;
    double tau;
    double aot;
    double moa;
    size_t nsim;
    size_t ndiv;
    double dt;
    rng_type rng;
    double oorm;
    
    Parameters(unsigned long seed, double mu, double a, double alpha, double tau, size_t nsim, size_t ndiv)
    {
        // rng
        rng_type rng(seed);
        rng.discard(1112239);
        this->rng = rng;

        // direct
        this -> mu = mu;
        this -> a = a;
        this -> alpha = alpha;
        this -> tau = tau;
        this -> nsim = nsim;
        this -> ndiv = ndiv;
        
        // derived
        this -> oomu = 1.0/mu;
        this -> oorm = 1.0/rng.max();
        this -> aot = alpha/tau;
        this -> moa = -1.0/alpha;
        this -> min_pareto = pow(tau, moa);
        this -> dt = 1.0/ndiv;
        
        
        // poisson
        this -> max_pois = MAXPOIS;
        double factorial = 1;
        double prob=0;
        for (int i=0; i<max_pois; i++) {
            prob = prob + exp(-a)*pow(a,i)/factorial;
            pois_prob.push_back(prob);
            factorial = factorial * (i+1);
        };
    }
    
    double phi(double x)
    {
        return( a*aot * pow((x+min_pareto), -1.0 - alpha) );
    };
    
};



double runif(Parameters &par)
{
    return (par.rng() * par.oorm);
}

// with parameter a
size_t rpois(Parameters &par)
{
    double x=runif(par);
    for (size_t i=0; i<par.max_pois; i++) {
        if (par.pois_prob[i]>x)
            return(i);
    };
    return(par.max_pois);
};

double rexp(Parameters &par)
{
    // theta = 1/mu
    return (-par.oomu * log(runif(par)));
};

double rpareto(Parameters &par)
{
    return (pow(par.tau*runif(par), -1.0 / par.alpha) - par.min_pareto);
};

void simulate_single_poisson(Parameters &par, vector<double> &p)
{
    
    double E = rexp(par);
    double N = E;

    while( N < 1.0) 
    {
        p.push_back(N);
        E = rexp(par);
        N = N + E;
    };
};

int hawksify(Parameters &par, std::vector<double> &p)
{

    if (p.size() == 0) return(0);
    
    size_t left = 0;
    size_t right = p.size();
    double point_candidate;
    double num_offspring;
    int num_gen = 0;

    // Continue while the previous generation is non-empty
    do    
    {
        num_gen++;
//        cout << endl << "Generation " << num_gen << endl << endl;
        
        // Loop through the previous generation
        for (size_t i = left; i < right; i++)
        {
            // for each, draw how many offspring
            num_offspring = rpois(par);
//            cout << p[i] << "(" << num_offspring << ")  \t-> ";

            for (size_t j = 0; j < num_offspring; j++)
            {
                // Draw a point candidate
                // double rp = rpareto(par);
                // point_candidate = p[i] + rp;
                // cout << rp << ", ";
                point_candidate = p[i] + rpareto(par);;

                // Add if does not fall outside of [0,1]
                if (point_candidate < 1.0)
                {
                    p.push_back(point_candidate);
//                    cout << point_candidate << ", ";
                };
            };
//            cout << endl;
        };

        // Generation built. 
        left = right;
        right = p.size();

    } while (left < right);

    return(num_gen);

}

void count(Parameters &par, vector<double> &p, vector<size_t> &counts, vector<double> &lambda, size_t current)
{
    for (auto &x : p)
    {
        counts[ current + size_t(x * par.ndiv) ]++;
        for( size_t i = size_t(1+x*par.ndiv); i < par.ndiv; i++)
            lambda[current+i] += par.phi(i*par.dt-x);
    };
    
};

// [[Rcpp::export]]
Rcpp::List simulate_hawkes(unsigned long seed, double mu, double a, double alpha, double tau, size_t nsim, size_t ndiv)
{
    Parameters par(seed, mu, a, alpha, tau, nsim, ndiv);
    
    vector<size_t> N(par.nsim * par.ndiv, 0);
    vector<double> lambda(par.nsim * par.ndiv, par.mu);
    
    size_t current = 0;
    int num_gen;

    for (size_t i = 1; i <= par.nsim; i++)
    {
        vector<double> p;
        simulate_single_poisson(par,p);
        // cout << p.size() << " - ";
        num_gen = hawksify(par,p);
        // cout << num_gen << ", ";
        count(par, p, N, lambda, current);
        current += par.ndiv;

        progress_bar(i, par.nsim);
    };
    
    Rcpp::List ret;
    ret["N"] = Rcpp::as<Rcpp::NumericVector>(Rcpp::wrap(N));
    ret["ld"] = Rcpp::as<Rcpp::NumericVector>(Rcpp::wrap(lambda));
    return ret;
    }

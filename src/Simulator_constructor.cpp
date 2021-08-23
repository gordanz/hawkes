#include <vector>
#include <cmath>
#include <ctime>
#include <iostream> // for debugging

#include "Simulator.hpp"
#define RANDMAX 4294967295

using namespace std;
Simulator::Simulator(double a, double alpha, double mu, double tau, size_t ndiv, size_t nsim, int id) 
    : a (a)
    , alpha (alpha)
    , mu (mu)
    , tau (tau)
    , ndiv ( ndiv)
    , nsim ( nsim )
    , id ( id)
{

    // compute the values for derived constants
    oomu = 1.0 / mu;
    oorm = 1.0 / RANDMAX;
    aalot = a * alpha / tau;
    mooal = -1.0 / alpha;
    min_pareto = pow(tau, mooal);
    dt = 1.0 / ndiv;
    nout = nsim*ndiv;

    // compute poisson probabilities
    double prob = 0;
    double prob_i = exp(-a);
    int i = 1;
    do
    {
        prob = prob + prob_i;
        pois_prob.push_back(prob);
        prob_i *= a / i;
        i++;
    } while (i < 30);

    // seed the rng
    unsigned long time_seed =  
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::milliseconds(1);
    // TODO: Make the id input better (second arg?)
    rng.seed(id*time_seed);

    // reserve space for vectors
    points.reserve( size_t( mu / (1.0 - a) ) );
    N.resize(nsim * ndiv,0.0);
    ld.resize(nsim * ndiv,0.0);
};

double Simulator::phi(double x)
{
    return ( aalot * pow((x + min_pareto), -1.0 - alpha));
};



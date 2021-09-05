#include <vector>
#include <cmath>
#include <ctime>
#include <iostream> // for debugging

#include "HawkesSimulator.hpp"
#define RANDMAX 4294967295

using namespace std;
HawkesSimulator::HawkesSimulator(double a, double alpha, double mu, double sigma, size_t ndiv, size_t nsim, int id) 
    : a (a)
    , alpha (alpha)
    , mu (mu)
    , sigma (sigma)
    , ndiv ( ndiv)
    , nsim ( nsim )
    , id ( id)
{

    // compute the values for derived constants
    oomu   = 1.0 / mu;
    oorm   = 1.0 / RANDMAX;
    alsi   = alpha * sigma;
    ooal   = 1.0 / alpha;
    ooalsi = 1.0 / alsi;
    oosi   = 1.0 / sigma;
    aosi   = a * oosi;
    dt     = 1.0 / ndiv;
    mudt   = mu * dt;
    nout   = nsim*ndiv;

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
    L.resize(nsim * ndiv,0.0);
};

double HawkesSimulator::phi(double x)
{
    // To match the paper, we must have pdf (x) \sim x^(-1-alpha)
   return( aosi * pow( 1 + x * ooalsi , -1 - alpha) ); 
};

double HawkesSimulator::Phi(double x)
{
    // To match the paper, we must have cdf (x) \sim x^(-alpha)
    return(a* ( 1.0 - pow((1.0+ x * ooalsi), - alpha)));
};




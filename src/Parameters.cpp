#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>

#include "Parameters.hpp"
#include "myrandom.hpp" // for RANDMAX

Parameters::Parameters(double alpha_in, double a_in, double mu_in, double tau_in, size_t ndiv_in, size_t nsim_in, int nthr_in)
{
    alpha = alpha_in; a = a_in; mu = mu_in; tau = tau_in ; nsim = nsim_in; ndiv = ndiv_in; nthr = nthr_in;
    

    oomu = 1.0 / mu;
    oorm = 1.0 / RANDMAX;
    aot = alpha / tau;
    moa = -1.0 / alpha;
    min_pareto = pow(tau, moa);
    dt = 1.0 / ndiv;

    nout = nthr*nsim*ndiv;

    // Monitoring
    numrng =0; numpts=0; numrej=0;

    // poisson
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
};

double Parameters::phi(double x)
{
    return (a * aot * pow((x + min_pareto), -1.0 - alpha));
}

std::string Parameters::csv()
{
    std::stringstream ss;
    ss << "alpha,  a, mu, tau, ndiv, dt, nthr, nsim, numrng, numpts, numrej" << std::endl;
    ss <<alpha<<", "<<a<<", "<<mu<<", "<<tau<<", "<<ndiv<<", "<<dt<<", "<<nthr<<", "<<nsim<<", "<<numrng<<", "<<numpts<<", "<<numrej<< std::endl;

    return(ss.str());
};

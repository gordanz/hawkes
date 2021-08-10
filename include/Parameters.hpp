#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "stddef.h"
#include <vector>

class Parameters
{
    public:

    // Globals - Basic
    double muz, alpha;
    size_t nsim, ndiv, nout;
    int nthr;

    // Globals - Derived
    double a, tau, mu, oomu, oorm, aot, moa, dt, min_pareto;
    std::vector<double> pois_prob;

    // Globals - Monitoring
    size_t numrng, numpts, numrej;

    // The kernel
    double phi(double x);
    Parameters(double alpha_in, double a_in, double mu_in, double tau_in, size_t ndiv_in, size_t nsim_in, int nthr_in);
    std::string csv();
};

#endif // __PARAMETERS_H__
#include <cmath>
#include "Simulator.hpp"
// #include "pcg_random.hpp" // for rng_type

double Simulator::runif()
{
    return (rng() * oorm);
}

size_t Simulator::rpois()
{
    double x=runif();
    size_t i=0;
    while ( x > pois_prob[i] )
        i++;
    return(i);
}

double Simulator::rexp()
{
    // theta = 1/mu
    return (-oomu * log(runif()));
}

double Simulator::rpareto()
{
    return (pow(tau*runif(),  mooal ) - min_pareto);
}



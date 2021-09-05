#include <cmath>
#include "HawkesSimulator.hpp"
// #include "pcg_random.hpp" // for rng_type

double HawkesSimulator::runif()
{
    return (rng() * oorm);
}

size_t HawkesSimulator::rpois()
{
    double x = runif();
    size_t i = 0;
    while (x > pois_prob[i])
        i++;
    return (i);
}

double HawkesSimulator::rexp()
{
    // theta = 1/mu
    return (-oomu * log(runif()));
}

double HawkesSimulator::rpareto()
{
    return (alsi * (pow(runif(), -ooal) - 1));
}

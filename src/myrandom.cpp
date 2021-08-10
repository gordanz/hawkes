#include <cmath>
#include "myrandom.hpp"
#include "Parameters.hpp"

double runif(rng_type &rng, Parameters &p)
{
    p.numrng++;
    return (rng() * p.oorm);
}

size_t rpois(rng_type &rng, Parameters &p)
{
    double x=runif(rng,p);
    size_t i=0;
    while ( x > p.pois_prob[i] )
        i++;
    return(i);
}

double rexp(rng_type &rng, Parameters &p)
{
    // theta = 1/mu
    return (-p.oomu * log(runif(rng,p)));
}

double rpareto(rng_type &rng, Parameters &p)
{
    return (pow(p.tau*runif(rng, p), -1.0 / p.alpha) - p.min_pareto);
}

size_t rpoisson_process(rng_type &rng, cvector<double> &points, Parameters &p)
{
    
    double E = rexp(rng, p);
    double N = E;

    while( N < 1.0) 
    {
        points.push_back(N);
        p.numpts++;
        E = rexp(rng,p);
        N = N + E;
    };
    return(points.size());
}

std::vector<uint64_t> seeds_for_threads(uint64_t preseed, Parameters &p)
{
    if (preseed == 0)
        preseed = time(nullptr);
    
    std::vector<uint64_t> seeds;
    rng_type seed_rng( preseed ); 

    seed_rng.discard(1231241243);
    
    for (size_t i = 0; i < p.nthr ; i++)
        seeds.push_back(seed_rng());

    return(seeds);
}
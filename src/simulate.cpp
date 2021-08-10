#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "Parameters.hpp"
#include "cvector.hpp"
#include "myrandom.hpp"

#include "progress_bar.hpp"
#include "tictoc.hpp"


size_t hawksify(rng_type &rng, cvector<double> &points, Parameters &p)
{
    if (points.size() == 0) return(0);
    
    size_t left = 0;
    size_t right = points.size();
    double point_candidate;
    double num_offspring;
    size_t numgen = 0;

    do    
    {
        for (size_t i = left; i < right; i++)
        {
            num_offspring = rpois(rng, p);
            for (size_t j = 0; j < num_offspring; j++)
            {
                point_candidate = points[i] + rpareto(rng, p);;
                if (point_candidate < 1.0)
                {
                    points.push_back(point_candidate);
                    p.numpts++;
                }
                else
                    p.numrej++;
            };
        };
        left = right;
        right = points.size();
        numgen++;

    } while (left < right);

    return(numgen);
}

void compute_N_ld(cvector<double> &points, std::vector<size_t> &N, std::vector<double> &ld, size_t current, size_t offset, Parameters &p)
{
    for (size_t i = 0; i<points.size(); i++)
    {
        // the bin containing x (left end-point)
        size_t ix = size_t(points[i]/p.dt);
        
        // update counts
        N[offset+ current + ix ]++;
        
        // update lambda (trapezoidal rule)
        ld[offset + current+ix] += 0.5*p.phi((ix+1)*p.dt-points[i]);

        for( size_t j = ix+1; j<p.ndiv; j++)
            ld[offset+current+j] += 0.5* p.phi( j*p.dt-points[i]) + 0.5* p.phi((j+1)*p.dt-points[i]);
    };
}

std::string simulate_hawkes(int id, uint64_t seed, std::vector<size_t> &N, std::vector<double> &ld, Parameters &p)
{
    rng_type rng(seed);
    rng.discard(1112239);
    size_t numgen, pois_size;
    size_t offset = id*p.nsim*p.ndiv;
    cvector<double> points( int(p.mu/(1.0-p.a)) );
    
    for (size_t i = 0; i < p.nsim; i++)
    {
        if (id == 0)
            progress_bar(i, p.nsim);
        points.reset();
        pois_size = rpoisson_process(rng,points, p);
        numgen = hawksify(rng,points, p);
        compute_N_ld(points, N, ld, i*p.ndiv, offset, p);

      
    };
    if (id == 0)
        progress_bar(p.nsim, p.nsim);

    std::stringstream ost;
    ost << "(last sim) numgen = " << numgen << ", poispts = " << pois_size << ", totpts = " << points.size();
    return(ost.str());

 };


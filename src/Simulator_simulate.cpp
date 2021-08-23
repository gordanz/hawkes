#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "Simulator.hpp"

void Simulator::simulate_first_generation()
{

    double e = rexp();
    double x = e;

    while (x < 1.0)
    {
        points.push_back(x);
        e = rexp();
        x = x + e;
    };
}

size_t Simulator::hawksify()
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
            num_offspring = rpois();
            for (size_t j = 0; j < num_offspring; j++)
            {
                point_candidate = points[i] + rpareto();;
                if (point_candidate < 1.0)
                    points.push_back(point_candidate);
            };
        };
        left = right;
        right = points.size();
        numgen++;

    } while (left < right);

    return(numgen);
}

void Simulator::compute_N(size_t simulation_number)
{
    size_t offset = simulation_number * ndiv;
    for (auto x : points)
    {
        // update counts
        // size_t( x / dt) is the left-end point of the bin containing x
        N[ offset + size_t ( x / dt ) ]++;
    };
}

void Simulator::compute_ld(size_t simulation_number)
{
    size_t offset = simulation_number * ndiv;
    for (auto x : points)
    {
        // the bin containing x (left end-point)
        size_t ix = size_t( x / dt);
        
        // update lambda (trapezoidal rule)
        ld[ offset+ix] += 0.5*phi((ix+1)*dt- x);

        for( size_t j = ix+1; j < ndiv; j++)
            ld[ offset+j] += 0.5* phi( j*dt-x ) + 0.5* phi( (j+1)*dt-x );
    };
}


// std::string simulate_hawkes(int id, uint64_t seed, std::vector<size_t> &N, std::vector<double> &ld, Parameters &p)
// {
//     rng_type rng(seed);
//     rng.discard(1112239);
//     size_t numgen, pois_size;
//     size_t offset = id*p.nsim*p.ndiv;
//     cvector<double> points( int(p.mu/(1.0-p.a)) );
    
//     for (size_t i = 0; i < p.nsim; i++)
//     {
//         if (id == 0)
//             progress_bar(i, p.nsim);
//         points.reset();
//         pois_size = rpoisson_process(rng,points, p);
//         numgen = hawksify(rng,points, p);
//         compute_N_ld(points, N, ld, i*p.ndiv, offset, p);

      
//     };
//     if (id == 0)
//         progress_bar(p.nsim, p.nsim);

//     std::stringstream ost;
//     ost << "(last sim) numgen = " << numgen << ", poispts = " << pois_size << ", totpts = " << points.size();
//     return(ost.str());

//  };


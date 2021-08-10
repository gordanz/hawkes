#ifndef __MYRANDOM_HPP__
#define __MYRANDOM_HPP__

#include "pcg_random.hpp"
#include "cvector.hpp"
#include "Parameters.hpp"

#define RANDMAX 4294967295
#define THERNG pcg32
typedef THERNG rng_type;

double runif(rng_type &rng, Parameters &p);
size_t rpois(rng_type &rng, Parameters &p);
double rexp(rng_type &rng, Parameters &p);
double rpareto(rng_type &rng, Parameters &p);
size_t rpoisson_process(rng_type &rng, cvector<double> &points, Parameters &p);
std::vector<uint64_t> seeds_for_threads(uint64_t preseed, Parameters &p);

#endif // __MYRANDOM_HPP__
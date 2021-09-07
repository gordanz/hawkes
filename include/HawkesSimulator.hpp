#ifndef __SIMULATOR_HPP__
#define __SIMULATOR_HPP__

#include <cstddef>
#include <vector>
#include <string>
#include "cvector.hpp"

#include "pcg_random.hpp"
#include "Parameters.hpp"
typedef pcg32 rng_type;

class HawkesSimulator
{
public: // for testing only, really private

    // user supplied
    double a, alpha, mu, sigma;
    size_t ndiv, nsim;
    int id;
    std::string outdir;
    Parameters par; // packaged

    // derived
    double oomu, oorm, alsi, aosi, ooal, ooalsi, oosi, mudt, dt;
    size_t nout;

    // kernel
    double phi(double x);
    double Phi(double x);

    // containers
    cvector<double> points;
    std::vector<double> dN;
    std::vector<double> ld;
    std::vector<double> L;

    //rng
    std::vector<double> pois_prob;
    rng_type rng;
    double runif();
    size_t rpois();
    double rexp();
    double rpareto();

    // simulation functions
    void simulate_first_generation();
    size_t hawksify();
    void discretize_and_store(size_t simulation_number);

public:
    HawkesSimulator(Parameters par, int id);
    void run(bool pbar = false);
    void output();

    // io
    std::string info();
};

#endif // __SIMULATOR_HPP__
/**
 * @file HawkesSimulator.hpp
 * @author Gordan Zitkovic
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SIMULATOR_HPP__
#define __SIMULATOR_HPP__

#include <cstddef>
#include <vector>
#include <string>
#include "cvector.hpp"

#include "pcg_random.hpp"
#include "Parameters.hpp"
typedef pcg32 rng_type;

/**
 * @brief Simulates the Hawkes process
 * 
 */
class HawkesSimulator
{
private: 

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
    std::vector<double> N;
    std::vector<double> ld;
    std::vector<double> dL;
    std::vector<double> L;

    //rng
    std::vector<double> pois_prob;
    rng_type rng;
    double runif();
    size_t rpois();
    double rexp();
    double rpareto();

    // simulation functions
    /**
     * @brief Simulates the immigrants (generation 0). Results kept in
     * the (private) variable `points`.
     *
     */
    void simulate_first_generation();
    /**
     * @brief Adds subsequent generations after
     * `simulate_first_generation()` is called. Results kept in the
     * (private) variable `points`.
     *
     * @return size_t
     */
    size_t hawksify();
    /**
     * @brief Packs simulations from `points` into `ndiv` bins for easier plotting, etc.
     * 
     * @param simulation_number 
     */
    void discretize_and_store(size_t simulation_number);

public:
    /**
     * @brief Construct a new Hawkes Simulator object
     * 
     * @param par Of class Parameters
     * @param id id number of the simulation (useful when parallel
     * computations are run)
     */
    HawkesSimulator(Parameters par, int id);
    /**
     * @brief Run the simulation.  
     * 
     * @param pbar show the progress bar (false by default)
     */
    void run(bool pbar = false);
    /**
     * @brief Output the simulations to a file. 
     * 
     */
    void output();

    // io
    /**
     * @brief 
     * 
     * @return std::string 
     */
    std::string info();
};

#endif // __SIMULATOR_HPP__
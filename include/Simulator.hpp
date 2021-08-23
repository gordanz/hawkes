#ifndef __SIMULATOR_HPP__ 
#define __SIMULATOR_HPP__ 

#include <cstddef>
#include <vector>
#include "cvector.hpp"

#include "pcg_random.hpp" 
typedef pcg32 rng_type;


class Simulator 
{
    private:

    // user supplied 
    double a, alpha, mu, tau;
    size_t ndiv, nsim;
    int id;

    // derived
    double oomu, oorm, aalot, mooal, dt, min_pareto;
    size_t nout;
    std::vector<double> pois_prob;
    double phi(double x);

    // containers
    cvector<double> points;
    std::vector<double> N;
    std::vector<double> ld;

    //rng
    rng_type rng;
    double runif();
    size_t rpois();
    double rexp();
    double rpareto();

    // utilities
    bool progress_bar_enabled = false;
    void progress_bar(size_t i, size_t maxi);
    bool timer_enabled = false;
    void tic(std::string str);
    void toc(std::string str);

    // simulation functions
    void simulate_first_generation();
    size_t hawksify();
    void compute_N(size_t simulation_number); 
    void compute_ld(size_t simulation_number); 

    public: 
    
    Simulator(double a, double alpha, double mu, double tau, size_t ndiv, size_t nsim, int id);
    void use_progress_bar() { progress_bar_enabled = true; };
    void use_timer() { timer_enabled = true; };
    void test();

    // io
    std::string parameters_to_csv();
    std::string parameters_to_string();
    std::string info();
    
};

#endif // __SIMULATOR_HPP__ 
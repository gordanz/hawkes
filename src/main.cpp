#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <string>

#include "HawkesSimulator.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    double a_in     = 0.95;
    double alpha_in = 1.5;
    double mu_in    = 10.0;
    double sigma_in = 0.05;
    size_t ndiv_in  = 1000;
    size_t nsim_in  = 2000;
    size_t nthr     = 1;

    if (argc == 1)
    {
        std::cerr << "WARNING: No arguments supplied. Using baked-in parameters." << std::endl;
    } 
    else if (argc == 8) 
    {
        a_in     = stod(argv[1]);
        alpha_in = stod(argv[2]);
        mu_in    = stod(argv[3]);
        sigma_in = stod(argv[4]);
        ndiv_in  = stod(argv[5]);
        nsim_in  = stod(argv[6]);
        nthr     = stod(argv[7]);
    }
    else 
    {

        std::cerr << "Usage: " << argv[0] << " a alpha mu sigma ndiv nsim id" << std::endl;
        exit(EXIT_FAILURE);
    };

    int id_in = 1;

    HawkesSimulator S1(a_in, alpha_in, mu_in, sigma_in, ndiv_in, nsim_in, id_in);
    cout << S1.info() << endl;
    // S1.use_timer();
    // S1.test();
    S1.run(true, true);

    //     tic("");
    //     // Output vectors
    //     vector<size_t> N(p.nout, 0);
    //     vector<double> ld(p.nout, p.mu);
    //     toc("Time: ");

    //     // Main Loop
    //     vector<string> diagnostics(p.nthr);
    //     auto seeds = seeds_for_threads(0, p);

    //     omp_set_num_threads(p.nthr);
    // #pragma omp parallel
    //     {
    //         int id = omp_get_thread_num();
    //         diagnostics[id] = simulate_hawkes(id, seeds[id], N, ld, p);
    //     }

    //     // Post Diagnostics
    //     cout << p.csv();
    //     for (size_t i = 0; i < p.nthr; i++)
    //         cout << "thread " << i << ": " << diagnostics[i] << endl;

    //     // Output
    //     string outdir = "/Users/gordanz/.h/build/";
    //     write_string(outdir + "par.csv", p.csv());
    //     write_vector(outdir + "N.csv", N, p.ndiv);
    //     write_vector(outdir + "ld.csv", ld, p.ndiv);

    //     toc("Time: ");

    return (0);
}

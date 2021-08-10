#include <stdio.h>
#include <stddef.h>
#include <omp.h>
#include <iostream>
#include <string>
#include <vector>

// Essential
#include "Parameters.hpp"
#include "simulate.hpp"
#include "myrandom.hpp" // to seed the threads

// Output
#include "io.hpp"

// Info
#include "tictoc.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 8)
    {
        std::cout << "Need exactly 7 parameters, got " << argc-1 <<". Exiting." << std::endl;
        return(1);
    };
    
    Parameters p(
        stod(argv[1]),   // alpha
        stod(argv[2]),   // a
        stod(argv[3]),   // mu
        stod(argv[4]),   // tau 
        stod(argv[5]),   // ndiv
        stod(argv[6]),   // nsim 
        stod(argv[7])    // nthr 
    );

// int main()
// {
//     std::cout << "Using baked-in parameters." << std::endl;
//     Parameters p(
//             1.5,  // alpha
//             0.9,  // a
//             30.0,  // mu
//             10.0,  // tau 
//             1000,  // ndiv
//             10,  // nsim 
//                 8   // nthr 
//     );


    cout << p.csv(); 
    cout.flush();

    tic("");
    // Output vectors
    vector<size_t> N(p.nout, 0);
    vector<double> ld(p.nout, p.mu);
    toc("Time: ");

    // Main Loop
    vector<string> diagnostics(p.nthr);
    auto seeds = seeds_for_threads(0, p);

    omp_set_num_threads(p.nthr);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        diagnostics[id] = simulate_hawkes(id, seeds[id], N, ld, p);
    }

    // Post Diagnostics
    cout << p.csv();
    for (size_t i = 0; i < p.nthr; i++)
        cout << "thread " << i << ": " << diagnostics[i] << endl;

    // Output
    string outdir = "/Users/gordanz/.h/build/";
    write_string(outdir + "par.csv", p.csv());
    write_vector(outdir + "N.csv", N, p.ndiv);
    write_vector(outdir + "ld.csv", ld, p.ndiv);

    toc("Time: ");

    return (0);
}

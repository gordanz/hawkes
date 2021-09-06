#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <string>

#include "Parameters.hpp"
#include "HawkesSimulator.hpp"
#include "utilities.hpp" // for timing
// #include "io.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int nthr = 16;
    // Parameters par(argc, argv); // get pars from command line
    Parameters par(
        0.95, // a
        1.0, // alpha
        900, // mu
        0.1, // sigma
        1000, // ndiv
        1600/nthr, // nsim
        nthr // nthr    
    );

    std::cout << par.str() << std::endl;
    
    tic("");

    omp_set_num_threads(par.nthr);
    std::string output_dir;
    #pragma omp parallel
    {
        int id = omp_get_thread_num()+1;

        HawkesSimulator S(par, id);
        S.run(true);

        // output_dir = S.output("/Users/gordanz/.h/output/");
    };

    // concatenate outputs from all threads
    // std::string cat_dN_command = "cat " + output_dir + "dN_* > " + output_dir + "dN.csv";
    // system(cat_dN_command.c_str());
    // std::string cat_ld_command = "cat " + output_dir + "ld_* > " + output_dir + "ld.csv";
    // system(cat_ld_command.c_str());
    // std::string cat_L_command = "cat " + output_dir + "L_* > " + output_dir + "L.csv";
    // system(cat_L_command.c_str());

    toc("Time: ");

    

    return (0);
}

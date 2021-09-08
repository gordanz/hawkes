
#include <omp.h>
#include <iostream>
#include <string>

#include "Parameters.hpp"
#include "HawkesSimulator.hpp"
#include "utilities.hpp" // for timing


int main(int argc, char *argv[])
{

    Parameters par(
        argc, argv,
        0.95,                       // a
        1.0,                        // alpha
        900,                        // mu
        0.1,                        // sigma
        1000,                       // ndiv
        16,                         // nsim
        2,                          // nthr
        "/Users/gordanz/.h/output/" // outdir (must end with "/")
    );

    std::cout << par.info() << std::endl;
    
    tic("");
    omp_set_num_threads(par.nthr);
#pragma omp parallel
    {
        int id = omp_get_thread_num() + 1;
        HawkesSimulator S(par, id);
        S.run(true);
        S.output();
    };

    par.concatenate_outputs();

    
    toc("Time: ");

    return (0);
}

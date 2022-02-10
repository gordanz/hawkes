
#include <omp.h>
#include <iostream>
#include <string>

#include "Parameters.hpp"
#include "HawkesSimulator.hpp"
#include "utilities.hpp" // for timing
#include "debug.hpp"

int main(int argc, char *argv[])
{
    Parameters par(
        argc, argv,                 // use command line if supplied, otherwise 
                                    // use the default pars below:
        0.95,                       // a
        1.0,                        // alpha
        9,                          // mu
        0.1,                        // sigma
        1000,                       // ndiv
        16,                         // nsim
        2,                          // nthr
        "/Users/gordanz/.h/output/" // outdir (must end with "/")
    );

    dbg << "Getting parameters." << std::endl;
    dbg << par.info() << std::endl;
    
    tic();
    dbg << "Simulating. " << std::endl;
    omp_set_num_threads(par.nthr);
#pragma omp parallel
    {
        int id = omp_get_thread_num() + 1;
        HawkesSimulator S(par, id);
        S.run(true);
        if (id == 1)
        {
            dbg << "Writing to files. " << std::endl;
        };
            S.output();
    };
    dbg << "Concatenating files." << std::endl;
    par.concatenate_outputs();

    
    dbg << "Time: " << toc() << std::endl;

    return (0);
}

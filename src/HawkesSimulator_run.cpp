#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "HawkesSimulator.hpp"
#include "utilities.hpp"

void HawkesSimulator::run(bool pbar)
{
    for (size_t i = 0; i < nsim; i++)
    {
        if (id == 1 && pbar)
            progress_bar(i, nsim);

        points.reset();
        simulate_first_generation();
        hawksify();
        discretize_and_store(i);
    };
    // Only one parallel simulation should show the progress bar
    if (id == 1 && pbar)
        progress_bar(nsim, nsim);

};

#include <iostream>
#include <sstream>
#include "HawkesSimulator.hpp"

std::string HawkesSimulator::parameters_to_csv()
{
    std::stringstream ss;
    ss << "a, alpha, sigma, mu, ndiv, nsim, nthr" << std::endl;
    ss << a << ", "
       << alpha << ", "
       << sigma << ", "
       << mu << ", "
       << ndiv << ", "
       << nsim << std::endl;

    return(ss.str());
};

std::string HawkesSimulator::parameters_to_string()
{
    std::stringstream ss;
    ss << "a=" << a << "_"
       << "alpha=" << alpha << "_"
       << "sigma=" << sigma << "_" 
       << "mu=" << mu << "_"
       << "ndiv=" << ndiv << "_"
       << "nsim=" << nsim;
    return(ss.str());
};

std::string HawkesSimulator::info()
{
   std::stringstream ss;
   ss << "Parameters: " << parameters_to_string() << std::endl;
   return(ss.str());
}

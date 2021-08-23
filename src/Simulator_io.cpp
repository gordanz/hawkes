#include <iostream>
#include <sstream>
#include "Simulator.hpp"

std::string Simulator::parameters_to_csv()
{
    std::stringstream ss;
    ss << "a, alpha,  tau, mu, ndiv, nsim, nthr" << std::endl;
    ss << a <<", "
       << alpha << ", "
       << tau << ", "
       << mu << ", "
       << ndiv << ", "
       << nsim << std::endl;

    return(ss.str());
};

std::string Simulator::parameters_to_string()
{
    std::stringstream ss;
    ss << "a=" << a << "_"  
       << "alpha=" << alpha << "_"
       << "tau=" << tau << "_" 
       << "mu=" << mu << "_"
       << "ndiv=" << ndiv << "_"
       << "nsim=" << nsim;
    return(ss.str());
};

std::string Simulator::info()
{
   std::stringstream ss;
   ss << "Parameters: " << parameters_to_string() << std::endl;
   return(ss.str());
}

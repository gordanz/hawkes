#include <iostream>
#include <sstream>

#include "Parameters.hpp"

Parameters::Parameters(){

};

Parameters::Parameters(double a, double alpha, double mu, double sigma, size_t ndiv, size_t nsim, size_t nthr)
    : a(a), alpha(alpha), mu(mu), sigma(sigma), ndiv(ndiv), nsim(nsim), nthr(nthr) {};
                                                                        
Parameters::Parameters(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "WARNING: No arguments supplied. Using baked-in parameters." << std::endl;
    }
    else if (argc == 8)
    {
        a = std::stod(argv[1]);
        alpha = std::stod(argv[2]);
        mu = std::stod(argv[3]);
        sigma = std::stod(argv[4]);
        ndiv = std::stod(argv[5]);
        nsim = std::stod(argv[6]);
        nthr = std::stod(argv[7]);
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " a alpha mu sigma ndiv nsim id" << std::endl;
        exit(EXIT_FAILURE);
    };
};

std::string Parameters::csv()
{
    std::stringstream ss;
    ss << "a, alpha, sigma, mu, ndiv, nsim, nthr" << std::endl;
    ss << a << ", "
       << alpha << ", "
       << sigma << ", "
       << mu << ", "
       << ndiv << ", "
       << nsim << ", "
       << nthr << std::endl;

    return (ss.str());
};

std::string Parameters::str()
{
    std::stringstream ss;
    ss << "a=" << a << "_"
       << "alpha=" << alpha << "_"
       << "sigma=" << sigma << "_"
       << "mu=" << mu << "_"
       << "ndiv=" << ndiv << "_"
       << "nsim=" << nsim << "_"
       << "nthr=" << nthr;
    return (ss.str());
};

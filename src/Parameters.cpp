#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <string>

#include "Parameters.hpp"

Parameters::Parameters(){

};

Parameters::Parameters(double a, double alpha, double mu, double sigma,
                       size_t ndiv, size_t nsim, size_t nthr,
                       const char *outdir)
    : a(a), alpha(alpha), mu(mu), sigma(sigma),
      ndiv(ndiv), nsim(nsim), nthr(nthr), outdir(outdir){};

void Parameters::update_from_command_line(int argc, char *argv[])
{
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "hd::a::l::m::s::D::S::T::")) != -1)
    {
        switch (c)
        {

        case 'h':
            std::cout << "Usage:" << std::endl;
            std::cout << "  -h this help," << std::endl;
            std::cout << "  -d set output directory," << std::endl;
            std::cout << "  -a a," << std::endl;
            std::cout << "  -l alpha," << std::endl;
            std::cout << "  -s sigma," << std::endl;
            std::cout << "  -m mu," << std::endl;
            std::cout << "  -D ndiv," << std::endl;
            std::cout << "  -S nsim," << std::endl;
            std::cout << "  -T nthr." << std::endl;
            exit(EXIT_SUCCESS);
            break;

        case '0':
            std::cout << "Case 0" << std::endl;
            break;

        case 'd':
            outdir = optarg;
            break;

        case 'a':
            a = std::stod(optarg);
            break;

        case 'l':
            alpha = std::stod(optarg);
            break;

        case 'm':
            mu = std::stod(optarg);
            break;

        case 's':
            sigma = std::stod(optarg);
            break;

        case 'D':
            ndiv = std::stod(optarg);
            break;

        case 'S':
            nsim = std::stod(optarg);
            break;

        case 'T':
            nthr = std::stod(optarg);
            break;

        case '?':
            std::cerr << "Don't recognize the option \"-";
            fprintf(stderr, "%c", optopt);
            std::cerr << "\". Exiting." << std::endl;
            exit(EXIT_FAILURE);

        default:
            abort();
        }
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

std::string Parameters::info()
{
    std::stringstream ss;
    ss << "Parameters:" << std::endl
       << "  a = " << a << ", "
       << "alpha = " << alpha << ", "
       << "sigma = " << sigma << ", "
       << "mu = " << mu << ", "
       << "ndiv = " << ndiv << ", "
       << "nsim = " << nsim << ", "
       << "nthr = " << nthr << std::endl;
    ss << "  output dir = " << outdir;
    return (ss.str());
};

void Parameters::concatenate_outputs()
{
    std::vector<std::string> names{"dN", "ld", "L"};
    std::cout << "Concatenating output:" << std::endl;
    for (auto var : names)
    {
        std::string command = "cat " + outdir + var + "_* > " + outdir + var + ".csv";
        system(command.c_str());
        std::cout << "  " << command << std::endl;
    };
}

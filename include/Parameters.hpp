#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <cstdio>

class Parameters
{
public: // for now
    double a     = 0.95;
    double alpha = 1.5;
    double mu    = 100.0;
    double sigma = 0.05;
    size_t ndiv  = 100;
    size_t nsim  = 1;
    size_t nthr  = 1;

public:
    Parameters();
    Parameters(double, double, double, double, size_t, size_t, size_t);
    Parameters(int argc, char *argv[]);
    std::string csv();
    std::string str();
};


#endif // __PARAMETERS_H__
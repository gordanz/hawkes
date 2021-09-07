#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <cstdio>
#include <string>

class Parameters
{
public: // for now
    double a, alpha, mu, sigma;
    size_t ndiv, nsim, nthr;
    std::string outdir;

public:
    Parameters();
    Parameters(double, double, double, double, size_t, size_t, size_t, const char*);
    void update_from_command_line(int argc, char *argv[]);
    std::string csv();
    std::string str();
    std::string info();
    void concatenate_outputs();
};


#endif // __PARAMETERS_H__
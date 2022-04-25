/**
 * @file Parameters.hpp
 * @author Gordan Zitkovic 
 * @brief 
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define __PARAMETERS_H__

#include <cstdio>
#include <string>

/**
 * @brief A class that holds all parameters
 * 
 */
class Parameters
{
public: // for now
    double a; /*!< The expected number of offspring < 1 */
    double alpha; /*!< A parameter (exponent) of the Pareto kernel */
    double mu; /*!< Intensity of the ancestor PPP */
    double sigma; /*!< A parameter (scale) of the Pareto kernel */
    size_t ndiv; /*!< Number of divisions of [0,1] */
    size_t nsim; /*!< Number of simulated paths */
    size_t nthr; /*!< Number of threads (when using parallelization) */
    std::string outdir; /*!< Name of the output directory */

public:
    /**
     * @brief Construct a new Parameters object without initialization
     * 
     */
    Parameters();
    /**
     * @brief Construct a new Parameters object from command line arg or values
     * 
     * If command line arguments are given, Parameters will be filled
     * from there. The remaining arguments are values to be used for 
     * parameters not specified on the command line. 
     * 
     */
    Parameters(int, char **, double, double, double, double, size_t, size_t, size_t, const char *);
    /**
     * @brief A csv-formatted representation of parameters (for use with R)
     * 
     * @return std::string 
     */
    std::string csv();
    /**
     * @brief A human-readable string representation of parameters
     * without spaces. To be used as output file names.
     * 
     * @return std::string 
     */
    std::string str();
    /**
     * @brief A human-readable string representation. To be used for debugging.
     * 
     * @return std::string 
     */
    std::string info();
    /**
     * @brief Sends a command to the system to concatenate outputs of
     * different treads (something like `cat outdir/dN* > outdir/dN.csv`)
     * 
     */
    void concatenate_outputs();
};


#endif // __PARAMETERS_H__
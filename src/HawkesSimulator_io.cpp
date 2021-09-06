#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "HawkesSimulator.hpp"
#include "io.hpp"

std::string HawkesSimulator::info()
{
    std::stringstream ss;
    ss << "Parameters: " << par.str() << "_id=" << id << std::endl;
    return(ss.str());
};

std::string HawkesSimulator::output(std::string outdir)
{
      std::string dir = outdir + par.str()+"/";
      mkdir(dir.c_str(), 0755);

      if (id == 1)
         write_string_to_file(dir + "par.csv", par.csv());

      std::stringstream ss;
      ss << std::setw(3) << std::setfill('0') << id;
      std::string idstr = ss.str();

      std::string dN_full =  dir+"dN_"+idstr+".csv";
      std::string ld_full =  dir+"ld_"+idstr+".csv";
      std::string L_full =  dir+"L_"+idstr+".csv";

      write_vector_as_matrix_to_file(dN_full, dN, ndiv);
      write_vector_as_matrix_to_file(ld_full, ld, ndiv);
      write_vector_as_matrix_to_file(L_full, L, ndiv);

      return(dir);
};

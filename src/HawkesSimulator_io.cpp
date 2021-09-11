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
    ss << "Output directory: " << par.outdir << std::endl;
    return(ss.str());
};

void HawkesSimulator::output()
{
      mkdir(outdir.c_str(), 0755);

      if (id == 1)
      {
        write_string_to_file(outdir + "par.csv", par.csv());
      };

      std::stringstream ss;
      ss << std::setw(3) << std::setfill('0') << id;
      std::string idstr = ss.str();

      std::string dN_full =  outdir+"dN_"+idstr+".csv";
      std::string N_full =  outdir+"N_"+idstr+".csv";
      std::string ld_full =  outdir+"ld_"+idstr+".csv";
      std::string dL_full =  outdir+"dL_"+idstr+".csv";
      std::string L_full =  outdir+"L_"+idstr+".csv";

      write_vector_as_matrix_to_file(dN_full, dN, ndiv);
      write_vector_as_matrix_to_file(N_full, N, ndiv);
      write_vector_as_matrix_to_file(ld_full, ld, ndiv);
      write_vector_as_matrix_to_file(dL_full, dL, ndiv);
      write_vector_as_matrix_to_file(L_full, L, ndiv);
};

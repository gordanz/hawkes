#ifndef __IO_H__
#define __IO_H__

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <iomanip> // to set precision
#include <string>
#include <vector>

void write_string(std::string name, std::string str);

template <class T>
void write_vector(std::string name, std::vector<T> v, size_t period = SIZE_T_MAX)
{
    std::ofstream file;
    file.open(name);
    for (size_t i = 0; i < v.size(); i++)
    {
        file << v[i];
        if ((i + 1) % period == 0 || i + 1 == v.size())
            file << std::endl;
        else
            file << ", ";
    };
};

template< class T>
std::ostream &operator<<(std::ostream &output, std::vector<T> &v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        output << v[i];
        if (i + 1 < v.size())
            output << ", ";
    };
    return(output);
};


#endif // __IO_H__
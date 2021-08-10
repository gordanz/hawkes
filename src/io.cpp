#ifndef __IO_H__
#define __IO_H__

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <iomanip> // to set precision
#include <vector>

void write_string(std::string name, std::string str)
{
    std::ofstream file;
    file.open(name);
    file << str;
}

#endif // __IO_H__
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include "debug.hpp"

auto start = std::chrono::high_resolution_clock::now();
auto stop = std::chrono::high_resolution_clock::now();

void tic()
{
    start = std::chrono::high_resolution_clock::now();
}

std::string toc()
{
    std::stringstream ss;
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    start = stop;
    ss << duration.count() / 1000.0 << "s" << std::endl;
    return(ss.str());
}

void progress_bar(size_t i, size_t maxi)
{
    static int display_next = 0;
    int percent = (int)(100 * i) / maxi;
    if (percent >= display_next)
    {
        dbg << "\r"
                  << "  ["
                  << std::string(percent / 5, (char)43u)
                  << std::string(100 / 5 - percent / 5, ' ') << "] ";
        dbg << percent << "% ";
        dbg.flush();
        display_next += 1;
    };
    if (i == maxi)
        std::cout << std::endl;
};
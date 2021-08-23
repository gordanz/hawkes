#include <chrono>
#include <iostream>
#include <string>

#include "Simulator.hpp"

auto start = std::chrono::high_resolution_clock::now();
auto stop = std::chrono::high_resolution_clock::now();

void Simulator::tic(std::string str)
{
    if (timer_enabled) 
    {
        std::cout << str;
        std::cout.flush();
        start = std::chrono::high_resolution_clock::now();
    }
}

void Simulator::toc(std::string str)
{
    if (timer_enabled)
    {
        stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        start = stop;
        std::cout << str << duration.count() / 1000.0 << "s" << std::endl;
        std::cout.flush();
    }
}

void Simulator::progress_bar(size_t i, size_t maxi)
{
    if (progress_bar_enabled)
    {
        static int display_next = 0;
        int percent = (int)(100 * i) / maxi;
        if (percent >= display_next)
        {
            std::cout << "\r"
                    << "Simulating ["
                    << std::string(percent / 5, (char)43u)
                    << std::string(100 / 5 - percent / 5, ' ') << "] ";
            std::cout << percent << "% ";
            std::cout.flush();
            display_next += 1;
        };
        if (i == maxi)
            std::cout << std::endl;
    }
};
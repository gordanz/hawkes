#include <chrono>
#include <iostream>
#include <string>

auto start = std::chrono::high_resolution_clock::now();
auto stop = std::chrono::high_resolution_clock::now();

void tic(std::string str)
{
    std::cout << str;
    start = std::chrono::high_resolution_clock::now();
}

void toc(std::string str)
{
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    start = stop;
    std::cout << str << duration.count()/1000.0 << "s" << std::endl;
    std::cout.flush();
}
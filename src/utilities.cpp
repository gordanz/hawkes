#include <chrono>
#include <iostream>
#include <string>

auto start = std::chrono::high_resolution_clock::now();
auto stop = std::chrono::high_resolution_clock::now();

void tic(std::string str)
{
    std::cout << str;
    std::cout.flush();
    start = std::chrono::high_resolution_clock::now();
}

void toc(std::string str)
{
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    start = stop;
    std::cout << str << duration.count() / 1000.0 << "s" << std::endl;
    std::cout.flush();
}

void progress_bar(size_t i, size_t maxi)
{
    static int display_next = 0;
    int percent = (int)(100 * i) / maxi;
    if (percent >= display_next)
    {
        std::cout << "\r"
                  << "["
                  << std::string(percent / 5, (char)43u)
                  << std::string(100 / 5 - percent / 5, ' ') << "] ";
        std::cout << percent << "% ";
        std::cout.flush();
        display_next += 1;
    };
    if (i == maxi)
        std::cout << std::endl;
};
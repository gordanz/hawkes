#include <iostream>
#include <string>

void progress_bar(size_t i, size_t maxi)
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
};

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "HawkesSimulator.hpp"

void HawkesSimulator::simulate_first_generation()
{

    double e = rexp();
    double x = e;

    while (x < 1.0)
    {
        points.push_back(x);
        e = rexp();
        x = x + e;
    };
}

size_t HawkesSimulator::hawksify()
{
    if (points.size() == 0)
        return (0);

    size_t left = 0;
    size_t right = points.size();
    double point_candidate;
    double num_offspring;
    size_t numgen = 0;

    do
    {
        for (size_t i = left; i < right; i++)
        {
            num_offspring = rpois();
            for (size_t j = 0; j < num_offspring; j++)
            {
                point_candidate = points[i] + rpareto();
                if (point_candidate < 1.0)
                    points.push_back(point_candidate);
            };
        };
        left = right;
        right = points.size();
        numgen++;

    } while (left < right);

    return (numgen);
}

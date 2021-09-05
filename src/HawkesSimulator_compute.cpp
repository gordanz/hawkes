// #include <iostream>
// #include <vector>
#include <cmath>
#include "HawkesSimulator.hpp"

// void HawkesSimulator::compute_N(size_t simulation_number)
// {
//     size_t offset = simulation_number * ndiv;
//     for (auto p : points)
//     {
//         // size_t( x / dt) is the left-end point of the bin containing x
//         N[offset + size_t(p / dt)]++;
//     };
// }

// void HawkesSimulator::compute_L(size_t simulation_number)
// {
//     size_t offset = simulation_number * ndiv;

//     // initial values: mu * t
//     for (size_t j = 0; j < ndiv; j++)
//     {
//         L[offset+j] = (j+1) * mudt;
//     };

//     // additional values for each point
//     for (auto p : points)
//     {
//         // size_t(p/dt) is the bin number containing p (0 - ndiv-1)
//         for (size_t j = size_t( p / dt) ; j < ndiv; j++)
//             L[offset + j] += Phi( (j + 1) * dt - p);
//     };
// }

// void HawkesSimulator::compute_ld(size_t simulation_number)
// {
//     size_t offset = simulation_number * ndiv;

//     // initial values: mu
//     for (size_t j = 0; j < ndiv; j++)
//     {
//         ld[offset + j] =  mu;
//     };

//     // additional values for each point
//     for (auto p : points)
//     {
//         // ip = size_t(p/dt) is the bin number containing p (0 - ndiv-1)
//         for (size_t j = size_t(p / dt) + 1; j < ndiv; j++)
//             ld[offset + j] += phi(j * dt - p);
//     };
// }

void HawkesSimulator::discretize_and_store(size_t simulation_number)
{
    size_t offset = simulation_number * ndiv;
    size_t ip;

    // initial values (N is set to 0 when constructed)
    for (size_t j = 0; j < ndiv; j++)
    {
        // N[offset + j] = 0.0;
        L[offset + j] = (j + 1) * mudt;
        ld[offset + j] = mu;
    };

    for (auto p : points)
    {
        ip = size_t(p / dt); // the bin number containing p

        N[offset + ip]++;

        for (size_t j = ip; j < ndiv; j++)
        {
            L[offset + j] += Phi((j + 1) * dt - p);
            if (j > ip)
                ld[offset + j] += phi(j * dt - p); // predictable
        };
    };
}

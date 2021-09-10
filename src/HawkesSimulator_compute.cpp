#include <cmath>
#include "HawkesSimulator.hpp"

void HawkesSimulator::discretize_and_store(size_t simulation_number)
{
    size_t offset = simulation_number * ndiv;
    size_t ip;

    for (size_t j = 0; j < ndiv; j++)
    {
        // dN is set to 0 when constructed
        L[offset + j] = (j + 1) * mudt;
        ld[offset + j] = mu;
    };

    for (auto p : points)
    {
        ip = size_t(p / dt); // the bin number containing p

        dN[offset + ip]++;

        for (size_t j = ip; j < ndiv; j++)
        {
            L[offset + j] += Phi((j + 1) * dt - p);
            if (j > ip)
                ld[offset + j] += phi(j * dt - p); // predictable
        };
    };

    // Optional: Compute N and dL
    for (size_t i = 0; i < ndiv; i++)
    {
        if (i == 0)
        {
            N[offset + i] = dN[offset + i];
            dL[offset + i] = L[offset + i];
        }
        else
        {
            N[offset + i] = N[offset + i - 1] + dN[offset + i];
            dL[offset + i] = L[offset + i] - L[offset + i - 1];
        };
    };
}

#include <iostream>

#include "Simulator.hpp"
#include "io.hpp"
using namespace std;

void Simulator::test()
{
    // simulate_first_generation();
    // hawksify();
    points.push_back(0.55);

    cout << "Before: " << ld << endl;
    compute_ld(0);
    cout << "After: " << ld << endl;
    compute_ld(1);    
    cout << "End: " << ld << endl;



}


#include <iostream>
#include "goodvector.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Goodvector<int> v;
    v.data.push_back(11);
    v.data.push_back(11231);

    cout << v << endl;
    return (0);
}

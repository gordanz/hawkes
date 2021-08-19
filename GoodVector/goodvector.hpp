#ifndef __GOODVECTOR_H__
#define __GOODVECTOR_H__

#include <iostream>
#include <vector>

template <class Object>
class Goodvector 
{

public:
    std::vector<Object> data;

    Object operator[](size_t i)
    {
        return(data[i]);
    }
};

template< class Object>
std::ostream &operator<<(std::ostream &output, Goodvector<Object> &v)
{
    for (size_t i = 0; i < v.data.size(); i++)
    {
        output << v.data[i];
        if (i + 1 < v.data.size())
            output << ", ";
    };
    return(output);
};

#endif // _GOODVECTOR_
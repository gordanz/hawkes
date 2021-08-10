#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <iostream>
#include <vector>

template <class T>
class cvector
{
public:
    std::vector<T> data;
    size_t pos;
    cvector(size_t max_size)
    {
        data.reserve(max_size);
        pos=0;
    };
    
    void push_back(T x)
    {
        if (pos >= data.size())
            data.push_back(x);
        else
            data[pos] = x;
        pos++;
    };
    
    size_t size()
    {
        return(pos);
    };
    
    void reset()
    {
        pos=0;
    };
    
    T operator[](size_t i)
    {
        return(data[i]);
    }
};

template< class T>
std::ostream &operator<<(std::ostream &output, cvector<T> &v)
{
    for (size_t i = 0; i < v.pos; i++)
    {
        output << v.data[i];
        if (i + 1 < v.pos)
            output << ", ";
    };
    return(output);
};

#endif // __CVECTOR_H__
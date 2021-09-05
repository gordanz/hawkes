#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <iostream>
#include <iterator>
#include <vector>

template <class T>
class cvector
{
public:
    std::vector<T> data;
    typename std::vector<T>::iterator myend;

    cvector()
    {
        myend = data.end();
    };

    void reserve(size_t expected_size)
    {
        data.reserve(expected_size);
        myend = data.begin();
    };

    typename std::vector<T>::iterator begin()
    {
        return (data.begin());
    }

    typename std::vector<T>::iterator end()
    {
        return (myend);
    }
    void push_back(T x)
    {
        if (myend == data.end())
        {
            data.push_back(x);
            myend = data.end();
        }
        else
        {
            *myend = x;
            std::advance(myend, 1);
        };
    };

    size_t size()
    {
        return (std::distance(data.begin(), myend));
    };

    void reset()
    {
        myend = data.begin();
    };

    T operator[](size_t i)
    {
        return (data[i]);
    }
};

template <class T>
std::ostream &operator<<(std::ostream &output, cvector<T> &v)
{

    typename std::vector<T>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        output << *it;
        if (std::next(it) != v.end())
            output << ", ";
    };
    return (output);
};

#endif // __CVECTOR_H__
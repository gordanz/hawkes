/**
 * @file cvector.hpp
 * @author Gordan Zitkovic 
 * @brief cvector class-template implementation
 * 
 * Implementation of  cvector<T> class
 * 
 * @version 0.1
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <iostream>
#include <iterator>
#include <vector>

/**
 * @brief A vector class with memory reuse
 *
 * cvector<T> is like vector<T> but with the ability to
 * reuse the allocated memory. It carries its own myend interator and an
 * additional member reset which virtually clears the vector.
 *
 * @tparam T anything that can be used with vector<T>
 */
template <class T>
class cvector
{
public:
    std::vector<T> data; /*!< holds the data */
    typename std::vector<T>::iterator myend; /*! iterator to current end of vector */

    /**
     * @brief Construct a new cvector object
     * 
     */
    cvector()
    {
        myend = data.end();
    };

    /**
     * @brief Reserve memory.
     * 
     * Reserve memory for data without filling it with anything.
     * 
     * @param expected_size 
     */

    void reserve(size_t expected_size)
    {
        data.reserve(expected_size);
        myend = data.begin();
    };

    /**
     * @brief Return the iterator to the start
     * 
     * @return std::vector<T>::iterator 
     */

    typename std::vector<T>::iterator begin()
    {
        return (data.begin());
    }

    /**
     * @brief Return the iterator to end (myend)
     * 
     * @return std::vector<T>::iterator 
     */

    typename std::vector<T>::iterator end()
    {
        return (myend);
    }

    /**
     * @brief Push x to the back of the cvector.
     * 
     * @param x 
     */
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

    /**
     * @brief Return the size of (the used portion of) cvector
     * 
     * @return size_t 
     */
    size_t size()
    {
        return (std::distance(data.begin(), myend));
    };

    /**
     * @brief Empty the vector without deallocating memory
     * 
     */
    void reset()
    {
        myend = data.begin();
    };

    /**
     * @brief Access element at position i
     * 
     * @param i position
     * @return T value
     */

    T operator[](size_t i)
    {
        return (data[i]);
    }
};

/**
 * @brief Print the contents of cvector to a stream
 * 
 * @tparam T 
 * @param output 
 * @param v 
 * @return std::ostream& 
 */

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
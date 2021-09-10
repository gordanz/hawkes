#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>

#define debug 1 
#define detailed_debug 0

#define dbg  \
    if (!(debug)) {} \
    else std::cerr

#define ddbg  \
    if (!(detailed_debug & debug)) {} \
    else std::cerr

#endif // __DEBUG_H__
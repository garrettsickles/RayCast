#ifndef _LOCAL_H_
#define _LOCAL_H_

#include <stdint.h>

// No Intersection array (NaN, NaN, NaN, Infinity)
static const uint64_t NO_INTERSECT_BITS[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };
static const double* NO_INTERSECT = (const double*)(NO_INTERSECT_BITS);

#endif
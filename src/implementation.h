#ifndef _IMPLEMENTATION_H_
#define _IMPLEMENTATION_H_

#include <math.h>
#include <float.h>
#include <stdint.h>

// Do not backshoot Rays
#define _RAYCAST_CULL_BACKSHOOT_

// No Intersection array (NaN, NaN, NaN, Infinity)
static const uint64_t NO_INTERSECT_BITS[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };
static const double* NO_INTERSECT = (const double*)(NO_INTERSECT_BITS);
static const double RAYCAST_EPSILON_POS =  DBL_EPSILON;
static const double RAYCAST_EPSILON_NEG = -DBL_EPSILON;

#endif
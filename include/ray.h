#ifndef _RAY_H_
#define _RAY_H_

#define _USE_INTRINSICS_

#ifdef _USE_INTRINSICS_

#include <immintrin.h>

extern __m256d RayIntoSphere(__m256d origin, __m256d direction, __m256d center, double radius);

#endif

#endif

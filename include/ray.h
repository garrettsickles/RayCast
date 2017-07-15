#ifndef _RAY_H_
#define _RAY_H_

#include <immintrin.h>

typedef __m256d Vector4;

extern Vector4 RayIntoSphere(Vector4 origin, Vector4 direction, Vector4 center, double radius);

#endif

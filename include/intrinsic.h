#ifndef _RAYCAST_INTRINSIC_H_
#define _RAYCAST_INTRINSIC_H_

// Use Intrinsic implementations
#define _RAYCAST_INTRINSIC_IMPLEMENTATION_ 1

// AVX2 + FMA Intrinsics
#include <immintrin.h>

// 256 bit Intrinsic (64 bit double by 4)
typedef __m256d Vector3;
typedef __m256d Vector4;

// Vector Accessors (platform dependent)
#if defined(_MSC_VER)
	#define X(v) v.m256d_f64[0]
	#define Y(v) v.m256d_f64[1]
	#define Z(v) v.m256d_f64[2]
	#define T(v) v.m256d_f64[3]
#elif defined(__GNUC__)
	#define X(v) v[0]
	#define Y(v) v[1]
	#define Z(v) v[2]
	#define T(v) v[3]
#endif

#endif
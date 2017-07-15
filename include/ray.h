#ifndef _RAY_H_
#define _RAY_H_

// 64 bit unsigned integer
#include <stdint.h>

// AVX2 + FMA Intrinsics
#include <immintrin.h>

// No Intersection array (NaN, NaN, NaN, Infinity)
static const uint64_t NO_INTERSECT[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };

// Compile messages
#define STRINGIFY(x) #x
#define LITERAL(x) STRINGIFY(x)

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

// ----------------------------------------
//                 API
// ----------------------------------------

// 256 bit Intrinsic (64 bit double by 4)
typedef __m256d Vector3;
typedef __m256d Vector4;

// Function:
//     Ray-Sphere Collision
//
// Input:
//     origin:
//         3D origin of the ray (T parameter currently unused)
//     direction:
//         3D direction of the ray (T parameter currently unused)
//     sphere:
//         3D origin of the sphere (T parameter as radius)
//
// Output:
//     intersection:
//         3D intersection of the ray and sphere (T parameter as time)

extern Vector4 RayIntoSphere(Vector3 origin, Vector3 direction, Vector4 sphere);

#endif

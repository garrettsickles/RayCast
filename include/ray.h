#ifndef _RAY_H_
#define _RAY_H_

// 64 bit unsigned integer
#include <stdint.h>

// AVX2 + FMA Intrinsics
#include <immintrin.h>

// ----------------------------------------
//                 API
// ----------------------------------------

// Stringify
#define STRINGIFY(x) #x
#define LITERAL(x) STRINGIFY(x)

// Shared Object
#if defined(_MSC_VER) && defined(_DLL)
	#define SHARED_EXPORT __declspec(dllexport)
#else
	#define SHARED_EXPORT
#endif

// Function builder
#define RAYCAST_IMPL(fn) Vector4 fn
#define RAYCAST_API(fn) extern SHARED_EXPORT RAYCAST_IMPL(fn)

// Function list
#define RAY_INTO_SPHERE RayIntoSphere

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

RAYCAST_API(RAY_INTO_SPHERE)(Vector3 origin, Vector3 direction, Vector4 sphere);

#endif

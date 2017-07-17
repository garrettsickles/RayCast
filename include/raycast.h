#ifndef _RAYCAST_H_
#define _RAYCAST_H_

#if defined(_MSC_VER) && defined(__AVX2__)
	#define __FMA__
#endif

#if defined(__AVX2__) && defined(__FMA__)
	#include <immintrin.h>

	typedef __m256d Vector3;
	typedef __m256d Vector4;

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

#else
	typedef struct Vector3 { double data[3]; } Vector3;
	typedef struct Vector4 { double data[4]; } Vector4;

	#define X(v) v.data[0]
	#define Y(v) v.data[1]
	#define Z(v) v.data[2]
	#define T(v) v.data[3]
#endif

// --------------------------------------------------------------------------------
//                      Section 2: Function Creation
// --------------------------------------------------------------------------------
// 
//  The function creation section specifies the preprocessor macros used in
//  building, implementing, maintaining, calling, an exporting API functions.
//
//  First things first, here is some cross platform nonsense to export symbols
//  on Windows. By definfing the preprocessor symbol _RAYCAST_DLL_,
//  RAYCAST_SHARED_EXPORT will only aplly on shared library Windows builds.

#if defined(_MSC_VER) && defined(_RAYCAST_DLL_)
	#define RAYCAST_SHARED_EXPORT __declspec(dllexport)
#else
	#define RAYCAST_SHARED_EXPORT
#endif

//  Next comes function building. All RayCast API ray-object casters return a
//  Vector4 containing < X, Y, Z, Time>. All functions are external symbols
//  and have the RAYCAST_SHARED_EXPORT prepended.

#define RAYCAST_FUNCTION(fn) Vector4 fn
#define RAYCAST_API(fn) extern RAYCAST_SHARED_EXPORT RAYCAST_FUNCTION(fn)

// --------------------------------------------------------------------------------
//                      Section 3: API List
// --------------------------------------------------------------------------------
//
//  This section is for conveinience more than anything. Following is a list of
//  symbols corresponding to the possible RayCast functions.

#define RAY_INTO_SPHERE        RayIntoSphere
#define RAY_INTO_TRIANGLE      RayIntoTriangle
#define RAY_INTO_PLANE         RayIntoPlane


// --------------------------------------------------------------------------------
//                                  Section 4: API
// --------------------------------------------------------------------------------
//
//  This section entails the formal API. It consists of preprocessor symbols,
//  flags, and function signatures.
//
//  The following is the list of API function calls for the RayCast API. Functions
//  will not have signature elsewhere.

// Function:
//     Ray-Sphere Intersection
//
// Input:
//     origin:
//         3D origin of the ray (T parameter currently unused)
//     direction:
//         3D direction of the ray (T parameter currently unused)
//     sphere:
//         3D center of the sphere (T parameter as radius)
//
// Output:
//     intersection:
//         3D intersection of the ray and sphere (T parameter as time scaled by length of direction)
//
RAYCAST_API(RAY_INTO_SPHERE)(Vector3 origin, Vector3 direction, Vector4 sphere);


// ----------------------------------------
// Function:
//     Ray-Triangle Intersection
//
// Note:
//     - The vertices A, B, and C should be specified in right handed (CCW) order
//     - If the vertices A, B, and C are not in right handed order,
//       the backface culling flag will not be used correctly
//
// Input:
//     origin:
//         3D origin of the ray (T parameter currently unused)
//     direction:
//         3D direction of the ray (T parameter currently unused)
//     vertex_a:
//         3D location of the A vertex (T parameter currently unused)
//     vertex_b:
//         3D location of the B vertex (T parameter currently unused)
//     vertex_c:
//         3D location of the C vertex (T parameter currently unused)
//     cull:
//         Flag specifying backface culling intersection with the triangle (False: Use Backface, True: Cull Backface)
//
// Output:
//     intersection:
//         3D intersection of the ray and triangle (T parameter as time scaled by length of direction)
//
RAYCAST_API(RAY_INTO_TRIANGLE)(Vector3 origin, Vector3 direction, Vector3 a, Vector3 b, Vector3 c, int cull);

// ----------------------------------------
// Function:
//     Ray-Plane Intersection
//
// Input:
//     origin:
//         3D origin of the ray (T parameter currently unused)
//     direction:
//         3D direction of the ray (T parameter currently unused)
//     vertex:
//         3D location of a point on the plane (T parameter currently unused)
//     normal:
//         3D direction of the plane's normal vector (T parameter currently unused)
//     cull:
//         Flag specifying backface culling intersection with the triangle (False: Use Backface, True: Cull Backface)
//
// Output:
//     intersection:
//         3D intersection of the ray and triangle (T parameter as time scaled by length of direction)
//
RAYCAST_API(RAY_INTO_PLANE)(Vector3 origin, Vector3 direction, Vector3 vertex, Vector3 normal, int cull);

#endif

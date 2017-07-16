#ifndef _RAYCAST_H_
#define _RAYCAST_H_

// Use Native C or Intinsics
#if 1
	#include "intrinsic.h"
#else
	#include "native.h"
#endif

// ----------------------------------------
//             API DEFINITIONS
// ----------------------------------------

// Stringify
#define RAYCAST_STRINGIFY(x) #x
#define RAYCAST_LITERAL(x) RAYCAST_STRINGIFY(x)

// Shared Object
#if defined(_MSC_VER) && defined(RAYCAST_DLL)
	#define RAYCAST_SHARED_EXPORT __declspec(dllexport)
#else
	#define RAYCAST_SHARED_EXPORT
#endif

// Function builder
#define RAYCAST_FUNCTION(fn) Vector4 fn
#define RAYCAST_API(fn) extern RAYCAST_SHARED_EXPORT RAYCAST_FUNCTION(fn)

// ----------------------------------------
//              API FUNCTIONS
// ----------------------------------------

// ---------- EXPORTED FUNCTIONS ----------
#define RAY_INTO_SPHERE        RayIntoSphere
#define RAY_INTO_TRIANGLE      RayIntoTriangle
// ----------------------------------------

// ----------------------------------------
// Function:
//     Ray-Sphere Collision
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
//     Ray-Triangle Collision
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
//     cull_backface:
//         Flag specifying backface culling intersection with the triangle (False: Use Backface, True: Cull Backface)
//
// Output:
//     intersection:
//         3D intersection of the ray and triangle (T parameter as time scaled by length of direction)
//
RAYCAST_API(RAY_INTO_TRIANGLE)(Vector3 origin, Vector3 direction, Vector3 vertex_a, Vector3 vertex_b, Vector3 vertex_c, int cull_backface);

#endif
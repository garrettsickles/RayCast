#include "implementation.h"
#include "raycast.h"

RAYCAST_FUNCTION(RAY_INTO_PLANE)(Vector3 origin, Vector3 direction, Vector3 vertex, Vector3 normal, int cull)
{
	double dot, time;
	Vector4 dotv, intersection;

	// Dot product of direction and normal vector
	dotv = _mm256_mul_pd(direction, normal);
	dot = X(dotv) + Y(dotv) + Z(dotv);

	// Parallel or backface
	if (dot > RAYCAST_EPSILON_NEG && (cull == 1  || dot < RAYCAST_EPSILON_POS))
	{
		return _mm256_load_pd(NO_INTERSECT);
	}

	// Compute intersection
	dotv = _mm256_mul_pd(_mm256_sub_pd(vertex, origin), normal);
	time = (X(dotv) + Y(dotv) + Z(dotv)) / dot;

	#if defined(_RAYCAST_CULL_BACKSHOOT_)
		// No backwards rays, otherwise this is a line intersection algorithm
		if (time < 0.0)
		{
			return _mm256_load_pd(NO_INTERSECT);
		}
	#endif

	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	T(intersection) = time;

	return intersection;
}
#include "implementation.h"
#include "raycast.h"

RAYCAST_FUNCTION(RAY_INTO_TRIANGLE)(Vector3 origin, Vector3 direction, Vector3 a, Vector3 b, Vector3 c, int cull)
{
	double determinant, u, v, time;
	Vector4 edge[2], pv, tv, uv, qv, vv, determinantv, intersection;
	
	// Edge vectors going to Vertex A
	edge[0] = _mm256_sub_pd(b, a);
	edge[1] = _mm256_sub_pd(c, a);

	// direction x edge[1]
	pv = _mm256_permute4x64_pd
		(
			_mm256_sub_pd(
					_mm256_mul_pd(direction, _mm256_permute4x64_pd(edge[1],   _MM_SHUFFLE(3, 0, 2, 1))),
					_mm256_mul_pd(edge[1],   _mm256_permute4x64_pd(direction, _MM_SHUFFLE(3, 0, 2, 1)))
			), _MM_SHUFFLE(3, 0, 2, 1)
		);

	// Determinant
	determinantv = _mm256_mul_pd(edge[0], pv);
	determinant = X(determinantv) + Y(determinantv) + Z(determinantv);

	if (determinant < RAYCAST_EPSILON_POS && (cull == 1  || determinant > RAYCAST_EPSILON_NEG))
	{
		return _mm256_load_pd(NO_INTERSECT);
	}
	
	// Displacement from Origin to Vertex A
	tv = _mm256_mul_pd(_mm256_sub_pd(origin, a), _mm256_set1_pd(1.0 / determinant));

	// Compute U parameter
	uv = _mm256_mul_pd(tv, pv);
	u = (X(uv) + Y(uv) + Z(uv));

	// No intersection
	if (u < 0.0 || u > 1.0)
	{
		return _mm256_load_pd(NO_INTERSECT);
	}

	// tv x edge[1]
	qv = _mm256_permute4x64_pd
		(
			_mm256_sub_pd(
					_mm256_mul_pd(tv,      _mm256_permute4x64_pd(edge[0], _MM_SHUFFLE(3, 0, 2, 1))),
					_mm256_mul_pd(edge[0], _mm256_permute4x64_pd(tv,      _MM_SHUFFLE(3, 0, 2, 1)))
			), _MM_SHUFFLE(3, 0, 2, 1)
		);

	// Compute V parameter
	vv = _mm256_mul_pd(direction, qv);
	v = (X(vv) + Y(vv) + Z(vv));

	// No intersection
	if (u < 0.0 || u + v > 1.0)
	{
		return _mm256_load_pd(NO_INTERSECT);
	}

	// Compute t parameter
	tv = _mm256_mul_pd(edge[1], qv);
	time = (X(tv) + Y(tv) + Z(tv));

	#if defined(_RAYCAST_CULL_BACKSHOOT_)
		// No backwards rays, otherwise this is a line intersection algorithm
		if (time < 0.0)
		{
			return _mm256_load_pd(NO_INTERSECT);
		}
	#endif
	
	// Compute intersection
	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	T(intersection) = time;

	return intersection;
}


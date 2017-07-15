#include "implementation.h"

RAYCAST_FUNCTION(RAY_INTO_TRIANGLE)(Vector3 origin, Vector3 direction, Vector3 vertex_a, Vector3 vertex_b, Vector3 vertex_c, int backface_cull)
{
	return _mm256_load_pd(NO_INTERSECT);
}
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

// No Intersection array (NaN, NaN, NaN, Infinity)
static const uint64_t NO_INTERSECT_BITS[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };
static const double* NO_INTERSECT = (const double*)(NO_INTERSECT_BITS);

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
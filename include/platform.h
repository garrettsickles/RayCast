#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#if defined(_MSC_VER)
	#define X(v) v.m256d_f64[0]
	#define Y(v) v.m256d_f64[1]
	#define Z(v) v.m256d_f64[2]
	#define T(v) v.m256d_f64[3]
#elif defined(__GNUC__) || defined(__GNUG__)
	#define X(v) v[0]
	#define Y(v) v[1]
	#define Z(v) v[2]
	#define T(v) v[3]
#endif

#endif
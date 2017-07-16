#ifndef _RAYCAST_NATIVE_H_
#define _RAYCAST_NATIVE_H_

// Use Native implementations
#define _RAYCAST_NATIVE_IMPLEMENTATION_ 1

// 256 bit Intrinsic (64 bit double by 4)
typedef struct Vector3 { double data[3]; } Vector3;
typedef struct Vector4 { double data[4]; } Vector4;

// Vector Accessors (platform independent)
#define X(v) v.data[0]
#define Y(v) v.data[1]
#define Z(v) v.data[2]
#define T(v) v.data[3]

#endif
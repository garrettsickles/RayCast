# RayCast  [![Build status: MSVC](https://ci.appveyor.com/api/projects/status/9c7uo3xxyguplf07?svg=true)](https://ci.appveyor.com/project/garrettsickles/raycast) [![Build Status: GCC](https://travis-ci.org/garrettsickles/RayCast.svg?branch=master)](https://travis-ci.org/garrettsickles/RayCast)

3D Ray casting in C using AVX2 and FMA intruction sets

### [**Current Release - v1.1.0**](https://github.com/garrettsickles/RayCast/releases/tag/v1.1.0)
## Example

The first step to using RayCast is to include [`raycast.h`](https://github.com/garrettsickles/RayCast/blob/master/include/raycast.h). This is the only file needed to use the library.

A simple program using the RayCast library could look like this
```C
#include <stdio.h>
#include "raycast.h"

int main()
{
    const Vector4 sphere       = {  0.0,  0.0,  0.0, 1.0 };
    const Vector3 origin       = {  1.0,  1.0,  1.0 };
    const Vector3 direction    = { -1.0, -1.0, -1.0 };
    const Vector4 intersection = RayIntoSphere(origin, direction, sphere);
    
    printf
    (
        "Intersection: <%lf, %lf, %lf, %lf>\n",
        X(intersection), Y(intersection), Z(intersection), T(intersection)
    );
    
    return 0;
}
```
And to compile in GCC simply run
```
gcc test.c -o test -L$(LIBRARY_PATH) -Wl,-rpath=$(LIBRARY_PATH) -lraycast -I$(INCLUDE_PATH) -mavx2 -mfma
```
where `LIBRARY_PATH` is the path to the build directory containing `libraycast.so` and `INCLUDE_PATH` is the path to the directory containing `raycast.h`.

And to execute run
```
./test
```
which outputs
```
Intersection: <0.577350, 0.577350, 0.577350, 0.422650>
```

## API

### Data Objects
| Object | Description |
| --- | --- |
| `Vector3` | A type containing three orthogonal scalars |
| `Vector4` | A type containing three orthogonal scalars and one miscellaneous scalar |

### [Ray-Sphere Intersection](https://github.com/garrettsickles/RayCast/blob/master/src/sphere.c)
| Parameter | Description |
| --- | --- |
| `Vector3 origin` |  Orthogonal coordinates of the beginning of the ray |
| `Vector3 direction` | Vector indicating positive direction of travel |
| `Vector4 sphere` |  Orthogonal coordinates of the center of the sphere with the radius appended |
```C
Vector4 RayIntoSphere(Vector3 origin, Vector3 direction, Vector4 sphere)
```

### [Ray-Triangle Intersection](https://github.com/garrettsickles/RayCast/blob/master/src/triangle.c)
| Parameter | Description |
| --- | --- |
| `Vector3 origin` |  Orthogonal coordinates of the beginning of the ray |
| `Vector3 direction` | Vector indicating positive direction of travel |
| `Vector3 a` |  Orthogonal coordinates of triangle vertex a |
| `Vector3 b` |  Orthogonal coordinates of triangle vertex b |
| `Vector3 c` |  Orthogonal coordinates of triangle vertex b |
| `int cull` |  Flag specifying whether to cull the backface intersection |
```C
Vector4 RayIntoTriangle(Vector3 origin, Vector3 direction, Vector3 a, Vector3 b, Vector3 c, int cull)
```

### [Ray-Plane Intersection](https://github.com/garrettsickles/RayCast/blob/master/src/plane.c)
| Parameter | Description |
| --- | --- |
| `Vector3 origin` |  Orthogonal coordinates of the beginning of the ray |
| `Vector3 direction` | Vector indicating positive direction of travel |
| `Vector3 vertex` |  Orthogonal coordinates of a vertex on the plane |
| `Vector3 normal` |  Vector in same direction as plane normal |
| `int cull` |  Flag specifying whether to cull the backface intersection |
```C
Vector4 RayIntoTriangle(Vector3 origin, Vector3 direction, Vector3 vertex, Vector3 normal, int cull)
```

## Build

### GCC
Run the makefile located in the `unix/gcc` directory with the parameter `CC` set to the GCC compiler command.

First:
```
cd unix/gcc
```

From Scratch:
```
make rebuild CC=$(COMPILER)
```

Static/Shared Libs:
```
make setup
make lib CC=$(COMPILER)
```

Tests:
```
make test CC=$(COMPILER)
```

where `COMPILER` is at least **`gcc-4.8`** or newer


### Windows
**Visual Studio:**
Visual Studio solutions are located in the `vs/$(VERSION)` directory where `VERSION` is the Visual studio distribution year

**Command line:**
```
vs\$(VERSION)\build_single.cmd $(CONFIGURATION)
```
where `CONFIGURATION` is **`"Debug"`**, **`"Release"`**, **`"Debug DLL"`**, or **`"Release DLL"`** or

```
vs\$(VERSION)\build.cmd
```
to build all configurations.

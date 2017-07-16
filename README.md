# RayCast  [![Build status: MSVC](https://ci.appveyor.com/api/projects/status/9c7uo3xxyguplf07?svg=true)](https://ci.appveyor.com/project/garrettsickles/raycast) [![Build Status: GCC](https://travis-ci.org/garrettsickles/RayCast.svg?branch=master)](https://travis-ci.org/garrettsickles/RayCast)

3D Ray casting in C using AVX2 and FMA intruction sets

### [**Current Release - v1.0.0**](https://github.com/garrettsickles/RayCast/releases/tag/v1.0.0)
## Example

The first step to using RayCast is to include `raycast.h`. This is the only file needed to use the library.

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

## Build

### GCC
Run the makefile located in the `unix/gcc` directory with the parameter `CC` set to the GCC compiler command.

```
cd unix/gcc
make lib CC=$(COMPILER)
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

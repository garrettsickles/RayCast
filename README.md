# RayCast  [![Build status: MSVC](https://ci.appveyor.com/api/projects/status/9c7uo3xxyguplf07?svg=true)](https://ci.appveyor.com/project/garrettsickles/raycast) [![Build Status: GCC](https://travis-ci.org/garrettsickles/RayCast.svg?branch=master)](https://travis-ci.org/garrettsickles/RayCast)

3D Ray casting in C using AVX2 and FMA intruction sets


## Build

### GCC
Run makefile located in 'unix/gcc' directory

```
cd unix/gcc
make all CC=$(COMPILER)
```
where `$COMPILER` is at least **`gcc-4.8`** or newer


### Windows
**Visual Studio:**
Visual Studio solutions are located in the `vs/$(VERSION)` directory where `$(VERSION)` is the Visual studio distribution year

**Command line:**
```
vs\$(VERSION)\build.cmd $(CONFIGURATION)
```
where `$(CONFIGURATION)` is **`"Debug"`**, **`"Release"`**, **`"Debug DLL"`**, or **`"Release DLL"`**

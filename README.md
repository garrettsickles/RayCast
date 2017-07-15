# RayCast [![Build status](https://ci.appveyor.com/api/projects/status/9c7uo3xxyguplf07?svg=true)](https://ci.appveyor.com/project/garrettsickles/raycast)
3D Ray casting in C using AVX2 and FMA intruction sets


## Build
Build Instructions

### GCC
Run makefile located in 'unix/gcc' directory

```
cd unix/gcc
make all
```


### Windows
**Visual Studio:**
Visual Studio solutions are located in the `vs/$(VERSION)` directory where `$(VERSION)` is the Visual studio distribution year

**Command line:**
```
vs\$(VERSION)\build.cmd $(CONFIGURATION)
```
where `$(CONFIGURATION)` is **`"Debug"`**, **`"Release"`**, **`"Debug DLL"`**, or **`"Release DLL"`**

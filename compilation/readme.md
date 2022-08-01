# Module 3: Building Scientific Software

## Preliminaries
Most scientific software is written in compiled programming languages such as C,
C++, and Fortran. Frequently, packages intended for use in scripting languages
(such as numpy and scipy) have components written in these languages.

For this module we will focus on programs written in C. Many important pieces of
software, scientific or not, are written in C, such as python, bash, most MPI
implementations, and PETSc. We will learn how to install two simple libraries,
both specific to this project and both containing deliberate bugs that you must
work around.

Software is not distributed as just source code - it also has a *build system*
which enables users to compile the software on their own terms. The two build
systems we will examine are autotools and CMake.

### libraryone: a deliberately buggy autotools library
Try to compile and install this library into a folder on your computer. To get
started: typically, when compiling software, we do an *out of source build*,
meaning that we create a separate build directory.

Try looking at some options with
```
./configure --help | less
```

The installation directory is specified with `--prefix`. See if you can work
around the bugs!

### librarytwo: use CMake
This one is more straightforward, but we need to provide the path of
`libraryone` to CMake. We can set up the project in a similar way:
```
mkdir build
cd build
cmake -DLIBRARYONE_ROOT=/path/to/libraryone \
      -DCMAKE_INSTALL_PREFIX=/path/to/install \
      ../
make install
```

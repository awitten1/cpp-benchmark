# C++ Benchmarking

This is a repo for me to learn about benchmarking C++ code using Google benchmark.

## Usage

To compile:
```
git submodule init
cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
```

To run the 2d array iteration (for example):
```
./2d-array
```
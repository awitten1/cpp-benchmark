# C++ Benchmarking

This is a repo for me to learn about benchmarking C++ code using Google benchmark.

## Usage

To compile:
```
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Running
```
./build/2d-array --benchmark_format=json  | jq '.benchmarks | .[] | {cpu_time: .cpu_time, name: .name}'
```
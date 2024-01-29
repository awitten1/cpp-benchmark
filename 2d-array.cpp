
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <thread>

#include <benchmark/benchmark.h>

static int** allocateArray(int rows, int cols) {
    int **ret = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        ret[i] = new int[cols];
    }
    return ret;
}

static void deleteArray(int **array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

static void experiment_row_order(benchmark::State& state) {
    int64_t nrows = state.range(0);
    int64_t ncols = state.range(0);

    auto array = allocateArray(nrows, ncols);

    for (auto _ : state) {
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                benchmark::DoNotOptimize(array[i][j]++);
            }
        }
    }

    deleteArray(array, nrows, ncols);
}

static void experiment_column_order(benchmark::State& state) {
    int64_t nrows = state.range(0);
    int64_t ncols = state.range(0);
    auto array = allocateArray(nrows, ncols);

    for (auto _ : state) {
        for (int j = 0; j < ncols; ++j) {
            for (int i = 0; i < nrows; ++i) {
                benchmark::DoNotOptimize(array[i][j]++);
            }
        }
    }

    deleteArray(array, nrows, ncols);
}

static void experiment_random_order(benchmark::State& state) {
    int64_t nrows = state.range(0);
    int64_t ncols = state.range(0);

    auto array = allocateArray(nrows, ncols);
    srand(0);

    for (auto _ : state) {
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                benchmark::DoNotOptimize(array[i][rand() % ncols]++);
            }
        }
    }
    deleteArray(array, nrows, ncols);
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
  for (int nrows : {32,64,128,256,512,1024,2048,8192})
    b->Arg(nrows);
}

BENCHMARK(experiment_row_order)->Apply(CustomArguments);
BENCHMARK(experiment_column_order)->Apply(CustomArguments);
BENCHMARK(experiment_random_order)->Apply(CustomArguments);

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);

    #if __cpp_lib_hardware_interference_size >= 201603
    benchmark::AddCustomContext("cache_line_size", std::hardware_destructive_interference_size);
    #endif

    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
}

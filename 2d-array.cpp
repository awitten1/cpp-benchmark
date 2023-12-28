
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <benchmark/benchmark.h>

constexpr size_t ncols = 10'000;
constexpr size_t nrows = 1'000;

static void experiment_row_order(benchmark::State& state) {
    auto array = new int[nrows][ncols];

    for (auto _ : state) {
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                benchmark::DoNotOptimize(array[i][j]++);
            }
        }
    }
    delete [] array;
}

static void experiment_column_order(benchmark::State& state) {
    auto array = new int[nrows][ncols];

    for (auto _ : state) {
        for (int j = 0; j < ncols; ++j) {
            for (int i = 0; i < nrows; ++i) {
                benchmark::DoNotOptimize(array[i][j]++);
            }
        }
    }
    delete [] array;
}

static void experiment_random_order(benchmark::State& state) {
    auto array = new int[nrows][ncols];
    srand(0);

    for (auto _ : state) {
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j) {
                benchmark::DoNotOptimize(array[i][rand() % ncols]++);
            }
        }
    }
    delete [] array;
}

BENCHMARK(experiment_row_order);
BENCHMARK(experiment_column_order);
BENCHMARK(experiment_random_order);

BENCHMARK_MAIN();


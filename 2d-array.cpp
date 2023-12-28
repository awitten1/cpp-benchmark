
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <benchmark/benchmark.h>

constexpr size_t size = 1'000;

static void experiment_row_order(benchmark::State& state) {
    state.PauseTiming();
    auto array = new int[size][size];
    state.ResumeTiming();

    for (auto _ : state) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                benchmark::DoNotOptimize(array[i][j]++);
            }
        }
    }
    state.PauseTiming();
    delete [] array;
}

static void experiment_column_order(benchmark::State& state) {
    state.PauseTiming();
    auto array = new int[size][size];
    state.ResumeTiming();

    for (auto _ : state) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                benchmark::DoNotOptimize(array[j][i]++);
            }
        }
    }
    state.PauseTiming();
    delete [] array;
}

static void experiment_random_order(benchmark::State& state) {
    state.PauseTiming();
    auto array = new int[size][size];
    srand(0);

    state.ResumeTiming();

    for (auto _ : state) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                benchmark::DoNotOptimize(array[i][rand() % size]++);
            }
        }
    }
    state.PauseTiming();
    delete [] array;
}

BENCHMARK(experiment_row_order);
BENCHMARK(experiment_column_order);
BENCHMARK(experiment_random_order);

BENCHMARK_MAIN();


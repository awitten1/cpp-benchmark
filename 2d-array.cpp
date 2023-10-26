
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iostream>

#include <benchmark/benchmark.h>


constexpr size_t size = 30'000;

static void experiment_row_major(benchmark::State& state) {
    state.PauseTiming();
    auto array = new int[size][size];
    state.ResumeTiming();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            array[i][j]++;
        }
    }
    state.PauseTiming();
    delete [] array;
}

static void experiment_column_major(benchmark::State& state) {
    state.PauseTiming();
    auto array = new int[size][size];
    state.ResumeTiming();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            array[j][i]++;
        }
    }
    state.PauseTiming();
    delete [] array;

}

BENCHMARK(experiment_row_major);
BENCHMARK(experiment_column_major);

BENCHMARK_MAIN();


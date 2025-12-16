#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>
#include <vector>
#include "functions.hpp"



static void BM_SumNumbers(benchmark::State& state) {
    volatile int x = warmup_cpu();
    auto nums = get_nums(state.range(0));
    for (auto _ : state)
        benchmark::DoNotOptimize(sum(nums));
}
BENCHMARK(BM_SumNumbers)->Arg(1 << 20);

BENCHMARK_MAIN();
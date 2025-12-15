#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>
#include <vector>

std::vector<long> get_nums(size_t num_elems) {
    std::vector<long> ret(num_elems);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> rng{};
    std::generate(ret.begin(), ret.end(), [&]() {
        return rng(gen);
    });
    return ret;
}

static int warmup_cpu() {
    int j = 0;
    for (int i = 0; i < 1 << 20; ++i) {
        j+= rand();
    }
    return j;
}


static long sum(const std::vector<long>& nums) {
    long ret = 0;
    for (auto num : nums) {
        ret += num;
    }
    return ret;
}

static void BM_SumNumbers(benchmark::State& state) {
    volatile int x = warmup_cpu();
    auto nums = get_nums(state.range(0));
    for (auto _ : state)
        benchmark::DoNotOptimize(sum(nums));
}
BENCHMARK(BM_SumNumbers)->Arg(1 << 20);


BENCHMARK_MAIN();
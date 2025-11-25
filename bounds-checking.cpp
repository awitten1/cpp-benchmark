
#include <benchmark/benchmark.h>


template<bool do_bounds_checks>
int sum(const std::vector<int>& arr) {
  int ret = 0;
  for (int i = 0; i < arr.size(); ++i) {
    if constexpr(do_bounds_checks) {
      ret += arr.at(i);
    } else {
      ret += arr[i];
    }
  }
  return ret;
}

template<bool do_bounds_checks>
void sum(benchmark::State& state) {
  std::vector<int> vec(100000);
  std::generate(vec.begin(), vec.end(), rand);

  for (auto _ : state) {
    benchmark::DoNotOptimize(sum<do_bounds_checks>(vec));
  }
}

BENCHMARK(sum<true>);
BENCHMARK(sum<false>);

BENCHMARK_MAIN();
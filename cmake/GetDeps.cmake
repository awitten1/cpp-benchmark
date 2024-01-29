
CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  VERSION 1.8.3
  OPTIONS "BENCHMARK_ENABLE_TESTING Off"
)

CPMAddPackage(
  NAME Boost_Container
  VERSION 1.81.0
  GITHUB_REPOSITORY "boostorg/boost"
  GIT_TAG "boost-1.81.0"
)

set(ABSL_PROPAGATE_CXX_STD ON)
CPMAddPackage(
  NAME abseil_cpp
  GITHUB_REPOSITORY "abseil/abseil-cpp"
  GIT_TAG 20240116.0
)





cmake_minimum_required(VERSION 3.16)

project("Benchmarking")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(CPM)
include(GetDeps)

add_executable(2d-array 2d-array.cpp)
set_target_properties(2d-array benchmark PROPERTIES CXX_STANDARD 17)
target_link_libraries(2d-array PRIVATE benchmark::benchmark)

add_executable(btree_benchmark btree_benchmark.cc)
set_target_properties(btree_benchmark benchmark PROPERTIES CXX_STANDARD 17)
target_link_libraries(btree_benchmark PUBLIC
  # google benchmark
  benchmark::benchmark

  # boost containers
  Boost::container
  Boost::unordered

  # abseil containers
  absl::btree
  absl::flat_hash_map
  absl::random_random
)

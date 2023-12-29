
cmake_minimum_required(VERSION 3.16)

project("Benchmarking")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  VERSION 1.8.3
  OPTIONS "BENCHMARK_ENABLE_TESTING Off"
)

# CPMAddPackage(
#   NAME Boost
#   VERSION 1.81.0
#   GITHUB_REPOSITORY "boostorg/boost"
#   GIT_TAG "boost-1.81.0"
# )

add_executable(2d-array 2d-array.cpp)
set_target_properties(2d-array benchmark PROPERTIES CXX_STANDARD 17)
target_link_libraries(2d-array PRIVATE benchmark::benchmark)

# add_executable(maps maps.cpp)
# set_target_properties(maps benchmark PROPERTIES CXX_STANDARD 17)
# target_link_libraries(maps PRIVATE
#   Boost::container
#   benchmark::benchmark
#   Boost::unordered
# )

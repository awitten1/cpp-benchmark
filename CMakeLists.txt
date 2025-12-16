
cmake_minimum_required(VERSION 3.24)

project(Benchmarking LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/install_dir")

find_package(benchmark REQUIRED)

add_executable(main main.cpp)
add_executable(perf_main perf_main.cpp)

target_link_libraries(main PRIVATE benchmark::benchmark)

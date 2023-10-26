
cmake_minimum_required(VERSION 3.16)

project("Know your hardware")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/submodules/benchmark/include)
add_subdirectory(submodules)
add_executable(2d-array 2d-array.cpp)
target_link_libraries(2d-array PRIVATE benchmark::benchmark)
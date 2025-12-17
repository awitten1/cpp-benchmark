#pragma once

#include <algorithm>
#include <random>
#include <vector>

std::vector<long> get_nums(size_t num_elems);

int warmup_cpu();

long sum(const std::vector<long>& nums);

long omp_sum(const std::vector<long>& nums);

size_t binary_search(const std::vector<long>& vec, long target);

size_t linear_search(const std::vector<long>& vec, long target);

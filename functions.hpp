#pragma once

#include <algorithm>
#include <random>
#include <vector>

std::vector<long> get_nums(size_t num_elems);

int warmup_cpu();

long sum(const std::vector<long>& nums);
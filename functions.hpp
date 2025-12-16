#pragma once

#include <algorithm>
#include <random>
#include <vector>

inline std::vector<long> get_nums(size_t num_elems) {
    std::vector<long> ret(num_elems);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> rng{};
    std::generate(ret.begin(), ret.end(), [&]() {
        return rng(gen);
    });
    return ret;
}

inline int warmup_cpu() {
    int j = 0;
    for (int i = 0; i < 1 << 20; ++i) {
        j+= rand();
    }
    return j;
}


inline long sum(const std::vector<long>& nums) {
    long ret = 0;
    for (auto num : nums) {
        ret += num;
    }
    return ret;
}
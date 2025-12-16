#include "functions.hpp"
#include <vector>
#include <omp.h>

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

int warmup_cpu() {
    int j = 0;
    for (int i = 0; i < 1 << 20; ++i) {
        j+= rand();
    }
    return j;
}


long sum(const std::vector<long>& nums) {
    long ret = 0;
    for (auto num : nums) {
        ret += num;
    }
    return ret;
}


long omp_sum(const std::vector<long>& nums) {
    long total_sum = 0;

    #pragma omp parallel for reduction(+:total_sum)
    for (size_t i = 0; i < nums.size(); ++i) {
        total_sum += nums[i];
    }
    return total_sum;
}


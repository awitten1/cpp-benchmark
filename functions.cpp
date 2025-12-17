#include "functions.hpp"
#include <cstddef>
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



size_t binary_search(const std::vector<long>& vec, long target) {
    size_t low = 0, high = vec.size();

    while (low < high) {
        size_t mid = low + (high - low)/2;
        if (vec[mid] < target) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

size_t linear_search(const std::vector<long>& vec, long target) {
    size_t idx = 0;
    for (; idx < vec.size(); ++idx) {
        if (vec[idx] >= target) {
            break;
        }
    }
    return idx;
}


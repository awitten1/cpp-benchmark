
#include "functions.hpp"
#include <chrono>
#include <csignal>
#include <ratio>
#include <string>
#include <unistd.h>
#include <iostream>

template<typename Func>
void RunUnderPerf(Func func, std::string output_file) {
    int pid = getpid();
    pid_t cpid = fork();
    if (cpid == 0) {
        char buf[50];
        sprintf(buf, "perf stat -ddd -p %d > %s 2>&1",pid, output_file.c_str());
        execl("/bin/sh", "sh", "-c", buf, NULL);
    }

    setpgid(cpid, 0);
    sleep(2);
    auto now = std::chrono::steady_clock::now();
    func();
    std::chrono::duration<double, std::milli> diff = std::chrono::steady_clock::now() - now;
    ::kill(-cpid, SIGINT);
    sleep(2);
    std::cout << "time " << diff.count() << " ms" << std::endl;
}


int main(int argc, char** argv) {
    auto nums = get_nums(std::stoi(argv[1]));
    RunUnderPerf([&nums]() {
        volatile long x = sum(nums);
    }, "stat.1.log");

    RunUnderPerf([&nums]() {
        volatile long x = omp_sum(nums);
    }, "stat.2.log");
    return 0;
}
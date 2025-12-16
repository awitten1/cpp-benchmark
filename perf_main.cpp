
#include "functions.hpp"
#include <chrono>
#include <csignal>
#include <ratio>
#include <string>
#include <unistd.h>
#include <iostream>

template<typename Func>
void RunUnderPerf(Func func) {
    int pid = getpid();
    pid_t cpid = fork();
    if (cpid == 0) {
        char buf[50];
        sprintf(buf, "perf stat -ddd -p %d > stat.log 2>&1",pid);
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
    RunUnderPerf([nums = std::move(nums)]() {
        volatile long x = sum(nums);
    });
    return 0;
}

#include "functions.hpp"
#include <csignal>
#include <string>
#include <unistd.h>

template<typename Func>
void RunUnderPerf(Func func) {
    pid_t cpid = vfork();
    int pid = getpid();
    if (cpid == 0) {
        char buf[50];
        sprintf(buf, "perf stat -p %d > stat.log 2>&1",pid);
        execl("/bin/sh", "sh", "-c", buf, NULL);
    }

    setpgid(cpid, 0);
    sleep(2);
    func();
    sleep(2);
    ::kill(-cpid, SIGINT);
}


int main(int argc, char** argv) {
    auto nums = get_nums(std::stoi(argv[1]));
    RunUnderPerf([nums = std::move(nums)]() {
        volatile int x = sum(nums);
    });
    return 0;
}
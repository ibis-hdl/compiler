#include <sys/types.h>

#include <iostream>

extern "C" {

pid_t getpid()
{
    // std::cout << "mock getpid()\n";
    return 1000;
}
}
#include <pthread.h>

#include <iostream>

extern "C" {

pthread_t pthread_self()
{
    // std::cout << "mock pthread_self()\n";
    return 1000000;
}
}
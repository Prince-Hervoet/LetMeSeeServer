#pragma once

#include <thread>

typedef void (*ThreadTaskFunc)(void *args);

namespace letMeSee
{
    class Thread
    {
    public:
        Thread();
        Thread(ThreadTaskFunc threadTaskFunc, void *args);
        ~Thread();
        void start();

    private:
        static void threadFunc(void *args);
        bool isStarted = false;
        std::thread::id tid;
        std::thread realThread;
        ThreadTaskFunc threadTaskFunc;
        void *args;
    };
}
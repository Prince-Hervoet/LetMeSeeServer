#pragma once

#include <semaphore.h>

namespace letMeSee
{
    /**
     * 信号量封装
     */
    class SemaphorePack
    {
    public:
        SemaphorePack();
        SemaphorePack(int value);
        ~SemaphorePack();

        void post();
        void wait();

    private:
        sem_t sem;
    };
}

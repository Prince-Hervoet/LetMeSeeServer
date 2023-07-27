#pragma once

#include <semaphore.h>

namespace letMeSee
{
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

#pragma once

#include <chrono>

#define DEFAULT_ROUTINE_STACK_SIZE 65536
#define DEFAULT_WORKER_ROUTINE_CAP 64

namespace letMeSee
{
    size_t getNowTimestampMs();

    class Task
    {
    public:
        virtual void run() = 0;
    };

}
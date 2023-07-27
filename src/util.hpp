#pragma once

#define DEFAULT_ROUTINE_STACK_SIZE 65536
#define DEFAULT_WORKER_ROUTINE_CAP 64

namespace letMeSee
{
    class Task
    {
    public:
        virtual void run() = 0;
    };
}
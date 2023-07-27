#pragma once

#include <chrono>

#define DEFAULT_ROUTINE_STACK_SIZE 65536
#define DEFAULT_WORKER_ROUTINE_CAP 64
#define DEFAULT_TASK_RUNTIME 16

namespace letMeSee
{
    /**
     * 获取当前时间戳ms
     */
    size_t getNowTimestampMs();

    /**
     * 获取当前时间戳ns
     */
    size_t getNowTimestampMic();

    class Task
    {
    public:
        virtual void run() = 0;
    };

}
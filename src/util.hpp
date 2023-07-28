#pragma once

#include <chrono>

// 默认协程栈大小
#define DEFAULT_ROUTINE_STACK_SIZE 65536

// 默认工作线程任务最大数
#define DEFAULT_WORKER_ROUTINE_CAP 64

// 默认工作线程数量
#define DEFAULT_WORKER_CAP 128

// 默认任务运行时间(ms)
#define DEFAULT_TASK_RUNTIME 16

// 默认epoll事件接收最大值
#define DEFAULT_EOPLL_EVENT_CAP 32

// 默认epoll等待时间(ms)
#define DEFAULT_EPOLL_WAIT_TIME 16

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
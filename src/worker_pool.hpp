#pragma once

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include "routine.hpp"

typedef void (*WorkerTaskFunc)(void *args);

#define DEFAULT_THREAD_CAP 32
#define DEFAULT_TASK_CAP 5000

namespace letMeSee
{
    class Worker
    {
    public:
        std::mutex mu;
        std::condition_variable cond;
        volatile bool isStoped = false;
        std::list<Routine *> tasks;
        Routine *running;

        Routine *pop();
        bool push(Routine *task);
        bool isEmpty();
    };

    class WorkerPool
    {
    public:
        WorkerPool();
        WorkerPool(int threadCapacity, int taskCapacity);
        ~WorkerPool();

        /**
         * 添加任务
         */
        int addTask(Routine *task);
        void stop();

    private:
        int threadCapacity = DEFAULT_THREAD_CAP;
        int taskCapacity = DEFAULT_TASK_CAP;
        int threadSize = 0;
        int taskSize = 0;

        static void workerFunc(void *args);
        void init();
    };
}
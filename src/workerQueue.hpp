#pragma once

#include <list>
#include "routine.hpp"
#include "thread.hpp"

namespace letMeSee
{
    struct WorkerTask
    {
        Routine *routine;
    };

    class Worker
    {
    public:
        Worker();
        ~Worker();

        bool addTask(WorkerTask *task);

    private:
        Thread *t;
        std::list<WorkerTask *> taskQueue;
    };

    class WorkerQueue
    {
    public:
        /**
         * 获取当前线程个数
         */
        int getThreadSize() const;

        bool createWorker(int count);

    private:
        static void threadTaskFunc(void *args);
        std::list<Worker *> workers;
    };
}
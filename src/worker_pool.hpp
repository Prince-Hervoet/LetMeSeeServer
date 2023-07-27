#pragma once

#include <vector>
#include "worker.hpp"
#include "sem_pack.hpp"
#include "util.hpp"

namespace letMeSee
{
    class WorkerPool
    {
    public:
        WorkerPool();
        WorkerPool(int workerCap, int workerTaskCap);
        ~WorkerPool();
        int addTask(Task *task);

    private:
        void init();
        int capacity;
        int taskSize;
        SemaphorePack sem = 1;
        std::vector<Worker *> workers;
    };
}
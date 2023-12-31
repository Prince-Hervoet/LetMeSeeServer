#pragma once

#include <list>
#include <queue>
#include "worker.hpp"
#include "routine_cache.hpp"
#include "./solve/pipeline.hpp"
#include "sem_pack.hpp"
#include "util.hpp"

namespace letMeSee
{
    typedef struct WorkerNode
    {
        Worker *worker;
        size_t expectTimestamp;

        bool operator<(const struct WorkerNode *other) const
        {
            return expectTimestamp < other->expectTimestamp;
        }
    } WorkerNode;

    class WorkerPool
    {
    public:
        WorkerPool();
        WorkerPool(int workerCap, int workerTaskCap);
        ~WorkerPool();

        void start();

        void setInPipeline(Pipeline *inPipeline);

        void setOutPipeline(Pipeline *outPipeline);

        /**
         * 添加任务到池中
         */
        int
        addTask(Task *task);

    private:
        /**
         * 监控线程执行函数
         */
        static void monitor(std::list<Worker *> &workers);

        /**
         * 计算期望时间戳
         */
        static size_t getExpect(size_t nowTimestamp, Worker *worker)
        {
            return nowTimestamp + worker->getSize() * DEFAULT_TASK_RUNTIME;
        }

        WorkerNode *createWorker();

        // 线程最大数量
        int workerCapacity;

        // 线程的任务最大数量
        int workerTaskCap;

        // 线程数
        int workerSize;
        SemaphorePack sem = 1;
        RoutineCache routineCache = 128;
        std::list<Worker *> workers;
        std::priority_queue<WorkerNode *> minHeap;
    };
}
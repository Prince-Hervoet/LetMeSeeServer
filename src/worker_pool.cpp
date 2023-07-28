#include "worker_pool.hpp"
#include "util.hpp"

namespace letMeSee
{
    WorkerPool::WorkerPool()
    {
        this->workerTaskCap = DEFAULT_WORKER_ROUTINE_CAP;
        this->workerCapacity = DEFAULT_WORKER_CAP;
    }

    WorkerPool::WorkerPool(int workerCap, int workerTaskCap)
        : workerCapacity(workerCap), workerTaskCap(workerTaskCap)
    {
    }

    WorkerPool::~WorkerPool()
    {
    }

    int WorkerPool::addTask(Task *task)
    {
        sem.wait();
        bool isOk = false;
        WorkerNode *node1 = minHeap.top();
        minHeap.pop();
        Worker *worker1 = node1->worker;
        Routine *routine = routineCache.get();
        routine->setTask(task);
        size_t nowTimestamp = getNowTimestampMs();
        isOk = worker1->push(routine);
        if (!isOk && (workerSize < workerCapacity))
        {
            WorkerNode *node2 = createWorker();
            Worker *worker2 = node2->worker;
            worker2->push(routine);
            node2->expectTimestamp = WorkerPool::getExpect(nowTimestamp, worker2);
            minHeap.push(node2);
            workerSize += 1;
            isOk = true;
        }
        if (!isOk)
            routineCache.push(routine);

        node1->expectTimestamp = WorkerPool::getExpect(nowTimestamp, worker1);
        minHeap.push(node1);
        sem.post();
        if (!isOk)
        {
            return 0;
        }
        return 1;
    }

    WorkerNode *WorkerPool::createWorker()
    {
        WorkerNode *node = new WorkerNode();
        node->expectTimestamp = 0;
        node->worker = new Worker();
        return node;
    }

    void WorkerPool::monitor(std::list<Worker *> &workers)
    {
        const size_t runtimeMic = DEFAULT_TASK_RUNTIME * 1000;
        for (;;)
        {
            size_t nowTimestamp = getNowTimestampMic();
            for (auto worker : workers)
            {
                size_t target = worker->getLastUpdateAt();
                if (target != -1 && nowTimestamp - target >= runtimeMic)
                {
                    // 发起中断信号
                    std::raise(worker->getWid());
                }
            }
        }
    }

}
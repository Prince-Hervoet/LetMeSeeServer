#include "worker_pool.hpp"

namespace letMeSee
{

    Routine *Worker::pop()
    {
        std::unique_lock<std::mutex> lock(mu);
        if (isEmpty())
        {
            cond.wait(lock);
        }
        Routine *task = tasks.front();
        tasks.pop_front();
        return task;
    }

    WorkerPool::WorkerPool()
    {
        init();
    }

    WorkerPool::WorkerPool(int threadCapacity, int taskCapacity)
    {
        this->threadCapacity = threadCapacity;
        this->taskCapacity = taskCapacity;
        init();
    }

    int WorkerPool::addTask(Routine *task)
    {
    }

    void WorkerPool::workerFunc(void *args)
    {
        Worker *worker = (Worker *)(args);

        while (!worker->isStoped)
        {
            Routine *task = worker->pop();
            worker->running = task;
            task->swapIn();
            task->reset();
            worker->running = nullptr;
        }
    }

    void WorkerPool::init()
    {
        for (int i = 0; i < threadCapacity / 2; i++)
        {
            std::thread t(WorkerPool::workerFunc);
        }
    }
}

#include "worker.hpp"

namespace letMeSee
{

    Worker::Worker()
        : capacity(DEFAULT_WORKER_ROUTINE_CAP), running(nullptr), taskSize(0)
    {
    }

    Worker::Worker(int capacity)
        : capacity(capacity), running(nullptr), taskSize(0)
    {
    }

    Worker::~Worker()
    {
    }

    Routine *Worker::pop()
    {
        std::unique_lock<std::mutex> lock(mu);
        if (isStoped)
        {
            return nullptr;
        }
        while (routines.size() == 0)
        {
            cond.wait(lock);
            if (isStoped)
            {
                return nullptr;
            }
        }
        Routine *task = routines.front();
        routines.pop_front();
        return task;
    }

    bool Worker::push(Routine *routine)
    {
        if (isStoped)
        {
            return false;
        }
        std::unique_lock<std::mutex> lock(mu);
        if (isStoped || (taskSize == capacity))
        {
            return false;
        }
        routines.push_back(routine);
        taskSize += 1;
        return true;
    }

    int Worker::getSize() const
    {
        return taskSize;
    }

    void Worker::start()
    {
        if (isStarted)
        {
            return;
        }
        isStarted = true;
        std::thread t(Worker::workerFunc, this);
    }

    void Worker::stop()
    {
        this->isStoped = true;
        this->cond.notify_all();
    }

    void Worker::workerFunc(void *args)
    {
        Worker *worker = (Worker *)args;
        while (!worker->isStoped)
        {
            Routine *routine = worker->pop();
            if (routine == nullptr)
            {
                break;
            }

            // 处理任务
            worker->swapIn(routine);
            if (routine->getStatus() == END)
            {
                // 执行结束切换过来，释放资源
                worker->taskSize -= 1;
            }
            else if (routine->getStatus() == PAUSE)
            {
                // 挂起切换过来的，放回队列尾部
                worker->push(routine);
            }
        }
    }

    void Worker::swapIn(Routine *routine)
    {
        switch (routine->getStatus())
        {
        case INIT:
            routine->init(DEFAULT_ROUTINE_STACK_SIZE);
        case READY:
            Routine::getContext(routine);
            Routine::setContext(routine, this->host);
            Routine::makeContext(routine);
            break;
        case PAUSE:
            break;
        default:
            return;
        }
        routine->setStatus(RUNNING);
        this->running = routine;
        this->lastUpdateAt = getNowTimestampMic();
        Routine::swapContext(routine, this->host);
    }

}
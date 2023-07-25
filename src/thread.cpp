#include "thread.hpp"

namespace letMeSee
{
    Thread::Thread(TaskFunc taskFunc, void *args, unsigned int customerId)
        : taskFunc(taskFunc), taskFuncArgs(args), customerId(customerId)
    {
    }

    Thread::~Thread()
    {
        if (this->realThread.joinable())
        {
            this->realThread.detach();
        }
    }

    void Thread::start()
    {
        if (isStarted)
        {
            return;
        }
        isStarted = true;
        realThread = std::thread(Thread::threadFunc, this);
    }

    void Thread::threadFunc(void *args)
    {
        Thread *t = (Thread *)(args);
        t->taskFunc(t->taskFuncArgs);
    }

}
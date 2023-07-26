#include "thread.hpp"

namespace letMeSee
{
    Thread::Thread() {}

    Thread::Thread(ThreadTaskFunc threadTaskFunc, void *args)
        : threadTaskFunc(threadTaskFunc), args(args)
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
        this->realThread = std::thread(Thread::threadFunc, this);
    }

    void Thread::threadFunc(void *args)
    {
        Thread *t = (Thread *)(args);
        try
        {
            t->threadTaskFunc(t->args);
        }
        catch (std::exception &e)
        {
        }
    }
}
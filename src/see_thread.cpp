#include "see_thread.hpp"
#include <iostream>

namespace letMeSee
{
    static thread_local SeeThread *tthread = nullptr;

    SeeThread::SeeThread(std::string &name, threadFunc func, void *args)
        : func(func), funcArgs(args)
    {
        if (name.empty())
        {
            this->name = "undefined";
        }
        else
        {
            this->name = name;
        }
    }

    SeeThread::~SeeThread()
    {
        if (this->realThread.joinable())
        {
            this->realThread.detach();
        }
    }

    void SeeThread::start()
    {
        this->realThread = std::thread(SeeThread::threadRun, this);
        this->tid = this->realThread.get_id();
        this->sem.wait();
    }

    SeeThread *SeeThread::GetThis()
    {
        return tthread;
    }

    const std::string &SeeThread::GetName()
    {
        return "";
    }

    void SeeThread::threadRun(void *args)
    {
        SeeThread *st = (SeeThread *)(args);
        tthread = st;
        pid_t pid = GetThreadId();
        st->sem.post();
        try
        {
            st->func(st->funcArgs);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

}
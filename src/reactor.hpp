#pragma once

#include "epoll_pack.hpp"
#include "thread.hpp"

#define DEFAULT_EPOLL_EVENT_MAX 32

namespace letMeSee
{
    class Reactor
    {
    public:
        Reactor();
        ~Reactor();

        void start();
        void addSocketFdToEpoll(int fd);

    private:
        static void eventLoop(void *args);
        volatile bool isStoped = false;
        EpollPack epollPack;
        Thread *t;
    };
}
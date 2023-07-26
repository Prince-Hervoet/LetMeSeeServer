#pragma once

#include "epoll_pack.hpp"

#define DEFAULT_EPOLL_EVENT_MAX 32

namespace letMeSee
{
    class Reactor
    {
    public:
        Reactor();
        ~Reactor();

        void addSocketFdToEpoll(int fd);
        void eventLoop();

    private:
        volatile bool isStoped = false;
        EpollPack epollPack;
    };
}
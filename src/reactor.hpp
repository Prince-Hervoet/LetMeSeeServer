#pragma once

#include <thread>
#include "epoll_pack.hpp"
#include "pipeline.hpp"

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
        void setInPipeline(Pipeline *inPipeline);
        void setOutPipeline(Pipeline *outPipeline);

    private:
        static void eventLoop(void *args);
        volatile bool isStoped = false;
        EpollPack epollPack;
        Pipeline *inPipeline;
        Pipeline *outPipeline;
    };
}
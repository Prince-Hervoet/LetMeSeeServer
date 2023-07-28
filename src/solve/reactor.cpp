#include "reactor.hpp"

namespace letMeSee
{
    void Reactor::start()
    {
        std::thread t(Reactor::eventLoopFunc, this);
    }

    void Reactor::eventLoopFunc(void *args)
    {

        Reactor *reactor = (Reactor *)args;
        struct epoll_event events[32];
        int res = 0;
        for (; !reactor->isStoped;)
        {
            // 在epoll中接收socket
            res = reactor->epollPack.epollWait(events, DEFAULT_EOPLL_EVENT_CAP, DEFAULT_EPOLL_WAIT_TIME);
            for (int i = 0; i < res; i++)
            {
            }
        }
    }

    void Reactor::setInPipeline(Pipeline *inPipeline)
    {
        this->inPipeline = inPipeline;
    }

    void Reactor::setOutPipeline(Pipeline *outPipeline)
    {
        this->outPipeline = outPipeline;
    }
}
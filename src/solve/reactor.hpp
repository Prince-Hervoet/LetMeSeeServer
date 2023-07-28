#pragma once

#include <thread>
#include "../epoll_pack.hpp"
#include "pipeline.hpp"
#include "../util.hpp"

namespace letMeSee
{
    class Reactor
    {
    public:
        Reactor();
        ~Reactor();

        void start();
        void stop();
        void setInPipeline(Pipeline *inPipeline);
        void setOutPipeline(Pipeline *outPipeline);

    private:
        /**
         * 事件循环执行函数
         */
        static void eventLoopFunc(void *args);

        bool isStoped;

        EpollPack epollPack;

        Pipeline *inPipeline;

        Pipeline *outPipeline;
    };
}
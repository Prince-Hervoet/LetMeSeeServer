#pragma once

#include <vector>
#include "reactor.hpp"
#include "pipeline.hpp"

#define DEFAULT_REACTOR_SIZE 8

namespace letMeSee
{
    class LmssApp
    {
    public:
        void startServer(int port);
        void setReactorSize(int size);
        void addInHandler();
        void addOutHandler();

    private:
        int currentReactorIndex = 0;

        std::vector<Reactor *> reactors;

        /**
         * 开始接受新连接
         */
        int acceptNewConnection(int port);

        /**
         * 将连接fd分给reactor
         */
        void giveConnection(int socketFd);

        /**
         * 入站通道
         */
        Pipeline *inPipeline;

        /**
         * 出站通道
         */
        Pipeline *outPipeline;
    };
}
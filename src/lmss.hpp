#pragma once

#include <vector>
#include "reactor.hpp"

#define DEFAULT_REACTOR_SIZE 8

namespace letMeSee
{
    class LmssApp
    {
    public:
        void startServer(int port);
        void addHandler();

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
    };
}
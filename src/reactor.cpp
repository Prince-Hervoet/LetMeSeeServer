#include "reactor.hpp"
#include <iostream>

namespace letMeSee
{
    void Reactor::start()
    {
        // 开启线程
        Thread *t = new Thread(Reactor::eventLoop, this);
        this->t = t;
        t->start();
    }

    void Reactor::addSocketFdToEpoll(int fd)
    {
        struct epoll_event *ev = this->epollPack.getEpollEvent();
        ev->events = EPOLLIN;
        ev->data.fd = fd;
        if (this->epollPack.epollCtl(EPOLL_CTL_ADD, fd) == -1)
        {
            std::cout << "error: epoll ctl" << std::endl;
        }
    }

    void Reactor::eventLoop(void *args)
    {
        Reactor *reactor = (Reactor *)(args);
        struct epoll_event events[DEFAULT_EPOLL_EVENT_MAX];
        for (; !reactor->isStoped;)
        {
            int resCount = reactor->epollPack.epollWait(events, DEFAULT_EPOLL_EVENT_MAX, -1);
            if (resCount == -1)
            {
                std::cout << "error: epoll wait" << std::endl;
            }

            for (int i = 0; i < resCount; i++)
            {
            }

            // todo: 处理定时任务
        }
    }
}
#include "epoll_pack.hpp"

EpollPack::EpollPack()
{
    int epollFd = epoll_create1(1);
    if (epollFd == -1)
    {
        // todo: 错误处理
    }
    this->epollFd = epollFd;
}

EpollPack::~EpollPack()
{
    close(this->epollFd);
}

int EpollPack::epollCtl(int op, int fd)
{
    return epoll_ctl(this->epollFd, op, fd, &(this->ev));
}

int EpollPack::epollWait(struct epoll_event *events,
                         int maxevents, int timeout)
{
    return epoll_wait(this->epollFd, events, maxevents, timeout);
}

struct epoll_event *EpollPack::getEpollEvent()
{
    return &(this->ev);
}

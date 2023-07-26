#pragma once

#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

/**
 * epoll封装
 */
class EpollPack
{
public:
    EpollPack();
    ~EpollPack();

    int epollCtl(int op, int fd);
    int epollWait(struct epoll_event *events,
                  int maxevents, int timeout);
    struct epoll_event *getEpollEvent();

private:
    int epollFd;
    struct epoll_event ev;
};

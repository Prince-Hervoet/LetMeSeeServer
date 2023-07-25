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

    int epollCtl(int op, int fd, struct epoll_event *event);
    int epollWait(struct epoll_event *events,
                  int maxevents, int timeout);

private:
    int epollFd;
};

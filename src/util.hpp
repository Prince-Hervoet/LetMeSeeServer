#pragma once

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

namespace letMeSee
{
    /**
     * 获取线程id
     */
    pid_t GetThreadId();

    class Semaphore
    {
    public:
        /**
         * 创建信号量
         */
        Semaphore(unsigned int value = 0);

        /**
         * 销毁信号量
         */
        ~Semaphore();

        /**
         * 获取信号量，减一
         */
        void wait();

        /**
         * 释放信号量
         */
        void post();

    private:
        sem_t semVar;
    };

    class EpollPack
    {
    public:
    private:
        int epollFd;
    };
}
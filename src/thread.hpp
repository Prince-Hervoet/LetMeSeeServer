#pragma once

#include <thread>
#include <list>
#include "util.hpp"

namespace letMeSee
{
    /**
     * 线程封装类，用于包装真实线程
     */
    class Thread
    {
    public:
        Thread(TaskFunc taskFunc, void *args, unsigned int customerId);
        ~Thread();

        /**
         * 启动线程
         */
        void start();

    private:
        /**
         * 线程真实运行的函数
         */
        static void threadFunc(void *args);

        /**
         * 用户自定义标识id
         */
        unsigned int customerId;

        /**
         * linux线程id
         */
        pid_t pid;

        /**
         * 线程句柄
         */
        std::thread realThread;

        /**
         * 任务函数
         */
        TaskFunc taskFunc;

        /**
         * 任务函数参数
         */
        void *taskFuncArgs;

        /**
         * 是否启动了
         */
        bool isStarted;
    };
}
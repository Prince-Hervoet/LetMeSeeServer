#pragma once

#include <thread>
#include <string>
#include "util.hpp"

namespace letMeSee
{
    typedef void (*threadFunc)(void *);
    class SeeThread
    {
    public:
        /**
         * 构造函数
         */
        SeeThread(std::string &name, threadFunc func, void *args);
        ~SeeThread();

        /**
         * 启动线程实例（创建真实线程）
         */
        void start();

        /**
         * 获取线程实例
         */
        static SeeThread *GetThis();

        /**
         * 获取线程名称
         */
        static const std::string &GetName();

    private:
        /**
         * 线程启动执行的函数
         */
        static void threadRun(void *args);

    private:
        std::thread realThread;
        threadFunc func;
        void *funcArgs;
        std::thread::id tid;
        std::string name;
        Semaphore sem;
    };
}
#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "routine.hpp"
#include "util.hpp"

namespace letMeSee
{
    class Worker
    {
    public:
        Worker();
        Worker(int capacity);
        ~Worker();

        /**
         * 弹出一个任务
         */
        Routine *pop();

        /**
         * 加入一个任务
         */
        bool push(Routine *routine);

        /**
         * 获取任务数量
         */
        int getSize() const;

        /**
         * 获取最后一次更新时间戳
         */
        size_t getLastUpdateAt();

        /**
         * 设置最后一次更新时间戳
         */
        void setLastUpdateAt(size_t lastUpdateAt);

        /**
         * 启动worker线程，只能启动一次
         */
        void start();

        /**
         * 结束标记
         */
        void stop();

    private:
        /**
         * 线程执行的任务函数
         */
        static void workerFunc(void *args);

        /**
         * 切换到指定协程运行
         */
        void swapIn(Routine *routine);

        // 是否被停止
        volatile bool isStoped;

        // 是否被启动
        bool isStarted;

        // 最大任务容量
        int capacity;

        // 当前任务数量
        int taskSize;

        // 主协程的上下文
        ucontext_t host;

        // 当前正在运行的协程
        Routine *running;

        // 🔒
        std::mutex mu;

        // 条件变量
        std::condition_variable cond;

        // 协程队列
        std::list<Routine *> routines;

        size_t lastUpdateAt;
    };
}
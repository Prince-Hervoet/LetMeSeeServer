#pragma once

#include <iostream>
#include <ucontext.h>
#include <string.h>
#include "util.hpp"

namespace letMeSee
{
    /**
     * 协程状态
     */
    enum RoutineStatus
    {
        INIT,
        READY,
        RUNNING,
        PAUSE,
        END
    };

    typedef enum RoutineStatus RoutineStatus;

    class Routine
    {
    public:
        Routine();
        Routine(Task *task);
        ~Routine();

        /**
         * 获取rid
         */
        size_t getRid() const;

        /**
         * 获取栈指针
         */
        char *getStack(int &stackSize);

        /**
         * 获取上下文
         */
        ucontext_t &getCtx();

        /**
         * 获取协程状态
         */
        RoutineStatus getStatus() const;

        /**
         * 获取任务结构
         */
        Task *getTask();

        /**
         * 设置状态
         */
        void setStatus(RoutineStatus status);

        /**
         * 设置任务结构
         */
        void setTask(Task *task);

        /**
         * 初始化 -- ready
         */
        void init(int stackSize);

        /**
         * 清除内部属性
         */
        void clear();

        static void getContext(Routine *routine);
        static void setContext(Routine *routine, ucontext_t &host);
        static void makeContext(Routine *routine);
        static void swapContext(Routine *routine, ucontext_t &host);

    private:
        static void routineFunc(void *args);

        // 协程id
        size_t rid;

        // 协程状态
        RoutineStatus status;

        // 栈空间
        char *stack;

        // 栈大小
        int stackSize;

        // 上下文
        ucontext_t ctx;

        // 执行的任务
        Task *task;
    };
}
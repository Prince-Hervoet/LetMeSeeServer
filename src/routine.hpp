#pragma once

#include <iostream>
#include <ucontext.h>
#include <mutex>
#include <list>

typedef void (*RoutineFunc)(void *args);

#define DEFAULT_ROUTINE_STACK_SIZE 32768

namespace letMeSee
{
    class Scheduler;
    enum RoutineStatus
    {
        INIT,    // 初始化
        READY,   // 可运行
        RUNNING, // 运行中
        PAUSE,   // 暂停
        END      // 运行结束
    };

    typedef enum RoutineStatus RoutineStatus;

    class Routine
    {
    public:
        Routine();
        ~Routine();

        /**
         * 重置参数，rid不会重置
         */
        void reset();

        /**
         * 获取栈指针
         */
        char *getStack(int &stackSize);

        /**
         * 获取上下文
         */
        ucontext_t &getCtx();

        /**
         * 获取任务函数
         */
        RoutineFunc getTaskFunc();

        /**
         * 获取任务函数参数
         */
        void *getArgs();

        /**
         * 设置状态
         */
        void setStatus(RoutineStatus status);

        /**
         * 切换到这个协程运行
         */
        void swapIn();

        /**
         * 将当前切换暂停切出
         */
        void swapOut();

    private:
        // 协程id
        size_t rid;
        // 状态
        RoutineStatus status;
        // 栈
        char *stack;
        // 栈大小
        int stackSize;
        // 上下文
        ucontext_t ctx;
        // 任务函数
        RoutineFunc taskFunc;
        // 参数
        void *args;
        // 所属的调度器
        Scheduler *sc;
    };

    class RoutineCache
    {
    public:
        RoutineCache();
        ~RoutineCache();
        Routine *pop();
        bool push(Routine *routine);

    private:
        int capacity = 0;
        std::list<Routine *> routines;
    };
}
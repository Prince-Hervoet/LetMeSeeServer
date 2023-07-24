#pragma once

#include <ucontext.h>

// 初始化
#define INIT 1
// 执行中
#define RUNNING 2
// 可执行
#define READY 3
// 暂停
#define PAUSE 4
// 结束
#define END 5

#define DEFAULT_STACK_SIZE 65535

typedef void (*routineFunc)(void *args);

namespace letMeSee
{
    class Routine
    {
    public:
        Routine();
        Routine(routineFunc func, void *args, int stackSize);
        ~Routine();

        int getStatus() const;
        char *getStack(int *stackSize) const;
        ucontext_t &getCtx() const;

        void setRoutineFunc(routineFunc func, void *args);

        void setInitStatus();
        void setRunningStatus();
        void setReadyStatus();
        void setPauseStatus();
        void setEndStatus();

        void swapInThis();
        void swapOutThis();

        void clear();

    private:
        // 栈指针
        char *stack;
        // 栈大小
        int stackSize;
        // 协程状态
        int status;
        // 协程上下文
        ucontext_t ctx;
        // 协程任务函数
        routineFunc func;
        // 任务函数参数
        void *funcArgs;
    };

}
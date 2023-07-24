#pragma once

#include <ucontext.h>
#include <list>
#include <mutex>

// 默认的协程栈大小 32KB
#define DEFAULT_STACK_SIZE 32768

typedef void (*routineFunc)(void *args);

namespace letMeSee
{
    enum ROUTINE_STATUS
    {
        INIT = 1,
        RUNNING = 2,
        READY = 3,
        PAUSE = 4,
        END = 5
    };

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
        void setStatus(enum ROUTINE_STATUS nStatus);

        void swapInThis();
        void swapOutThis();

        void clear();

    private:
        // 栈指针
        char *stack;
        // 栈大小
        int stackSize;
        // 协程状态
        enum ROUTINE_STATUS status;
        // 协程上下文
        ucontext_t ctx;
        // 协程任务函数
        routineFunc func;
        // 任务函数参数
        void *funcArgs;
    };

    class RoutineCache
    {
    public:
        RoutineCache();
        RoutineCache(int capacity);

        void giveback(Routine *routinePack);
        void getRoutinePack() const;

    private:
        int capacity;
        std::mutex mu;
        std::list<Routine *> rlist;
    };

}
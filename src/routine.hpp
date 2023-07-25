#pragma once

#include <ucontext.h>
#include "util.hpp"

namespace letMeSee
{
    enum ROUTINE_STATUS
    {
        INIT,
        READY,
        RUNNING,
        PAUSE,
        END
    };

    class Routine
    {
    public:
        char *getStackPtr(int *stackSize) const;
        enum ROUTINE_STATUS getStatus() const;
        ucontext_t &getCtx();

        void swapIn();
        void swapOut();

    private:
        size_t rid;

        /**
         * 栈指针
         */
        char *stackPtr;

        enum ROUTINE_STATUS status;

        /**
         * 栈大小
         */
        int stackSize;

        /**
         * 上下文
         */
        ucontext_t ctx;

        TaskFunc taskFunc;

        void *taskFuncArgs;
    };
}
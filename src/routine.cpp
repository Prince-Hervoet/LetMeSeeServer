#include "routine.hpp"
#include "scheduler.hpp"
#include <string.h>

namespace letMeSee
{
    Routine::Routine() {}

    Routine::~Routine()
    {
        if (this->stack)
        {
            delete[] stack;
        }
    }

    void Routine::reset()
    {
        if (this->stack)
        {
            delete[] stack;
        }
        this->stack = nullptr;
        this->stackSize = 0;
        taskFunc = nullptr;
        args = nullptr;
        memset(&(this->ctx), 0, sizeof(this->ctx));
    }

    char *Routine::getStack(int &stackSize)
    {
        stackSize = this->stackSize;
        return this->stack;
    }

    ucontext_t &Routine::getCtx()
    {
        return this->ctx;
    }

    RoutineFunc Routine::getTaskFunc()
    {
        return this->taskFunc;
    }

    void *Routine::getArgs()
    {
        return this->args;
    }

    void Routine::setStatus(RoutineStatus status)
    {
        this->status = status;
    }

    void Routine::swapIn()
    {
        switch (this->status)
        {
        case INIT:
            this->stack = new char[DEFAULT_ROUTINE_STACK_SIZE];
            this->stackSize = DEFAULT_ROUTINE_STACK_SIZE;
            getcontext(&(this->ctx));
            this->ctx.uc_stack.ss_sp = this->stack;
            this->ctx.uc_stack.ss_size = DEFAULT_ROUTINE_STACK_SIZE;
            break;
        case READY:
            break;
        case PAUSE:
            break;
        default:
            return;
        }
        makecontext(&(this->ctx), (void (*)(void))(this->taskFunc), 0);
        this->status = RUNNING;
        }

}
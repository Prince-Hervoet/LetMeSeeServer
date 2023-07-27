#include "routine.hpp"

namespace letMeSee
{
    Routine::Routine()
    {
        this->status = INIT;
    }

    Routine::Routine(Task *task)
    {
        this->task = task;
        this->status = INIT;
    }

    Routine::~Routine()
    {
        if (stack)
            delete[] stack;
        if (task)
            delete task;
    }

    size_t Routine::getRid() const
    {
        return this->rid;
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

    RoutineStatus Routine::getStatus() const
    {
        return this->status;
    }

    Task *Routine::getTask()
    {
        return this->task;
    }

    void Routine::setStatus(RoutineStatus status)
    {
        this->status = status;
    }

    void Routine::setTask(Task *task)
    {
        this->task = task;
    }

    void Routine::init(int stackSize)
    {
        if (status != INIT)
        {
            return;
        }
        stack = new char[stackSize];
        this->stackSize = stackSize;
        this->status = READY;
    }

    void Routine::clear()
    {
        this->status = INIT;
        if (stack)
            delete[] stack;
        stack = nullptr;

        stackSize = 0;

        memset(&ctx, 0, sizeof(ctx));

        if (task)
            delete task;
        task = nullptr;
    }

    void Routine::getContext(Routine *routine)
    {
        if (routine == nullptr)
            return;
        getcontext(&(routine->ctx));
    }

    void Routine::setContext(Routine *routine, ucontext_t &host)
    {
        if (routine == nullptr)
            return;
        routine->ctx.uc_stack.ss_sp = routine->stack;
        routine->ctx.uc_stack.ss_size = routine->stackSize;
        routine->ctx.uc_link = &host;
    }

    void Routine::makeContext(Routine *routine)
    {
        if (routine == nullptr)
            return;

        makecontext(&(routine->ctx), (void (*)())Routine::routineFunc, 1, routine);
    }

    void Routine::swapContext(Routine *routine, ucontext_t &host)
    {
        if (routine == nullptr)
            return;

        swapcontext(&host, &(routine->ctx));
    }

    void Routine::routineFunc(void *args)
    {
        Routine *routine = (Routine *)args;
        try
        {
            routine->task->run();
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        routine->clear();
        routine->status = END;
    }

}
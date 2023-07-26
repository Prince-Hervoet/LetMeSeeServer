#pragma once

#include "routine.hpp"
#include <list>

namespace letMeSee
{
    class Scheduler
    {
    public:
        int getRoutineSize();
        int pushRoutine(Routine *routine);
        Routine *popRoutine();
        void start();
        void stop();

    private:
        ucontext_t host;
        Routine *running;
        std::list<Routine *> routines;
    };

}
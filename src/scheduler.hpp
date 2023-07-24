#pragma once

#include <vector>
#include <list>
#include "routine.hpp"
#include "see_thread.hpp"

namespace letMeSee
{
    class Scheduler
    {
    public:
        void start();
        int getRoutineSize() const;
        int getThreadSize() const;
        Routine *getRunning() const;
        void addTask(routineFunc func, void *args);

    private:
        Routine *running = nullptr;
        std::list<Routine *> taskQueue;
        std::vector<SeeThread *> threadQueue;
    };
}
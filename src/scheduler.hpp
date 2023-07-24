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
    private:
        std::list<Routine *> taskQueue;
        std::vector<SeeThread *> threadQueue;
    };
}
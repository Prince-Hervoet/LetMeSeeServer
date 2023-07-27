#pragma once

#include <list>
#include <mutex>
#include "routine.hpp"

namespace letMeSee
{
    class RoutineCache
    {
    public:
        RoutineCache(int capacity);
        ~RoutineCache();
        Routine *get();
        bool push(Routine *routine);

    private:
        int capacity;
        std::mutex mu;
        std::list<Routine *> routines;
    };
}
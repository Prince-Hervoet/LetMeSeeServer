#include "routine_cache.hpp"

namespace letMeSee
{
    RoutineCache::RoutineCache(int capacity)
    {
        this->capacity = capacity;
    }

    RoutineCache::~RoutineCache()
    {
        while (!routines.empty())
        {
            delete routines.front();
            routines.pop_front();
        }
    }

    Routine *RoutineCache::get()
    {
        std::unique_lock<std::mutex> lock(mu);
        if (routines.size() == 0)
        {
            return new Routine();
        }
        Routine *routine = routines.front();
        routines.pop_front();
        return routine;
    }

    bool RoutineCache::push(Routine *routine)
    {
        if (routine == nullptr)
        {
            return false;
        }
        std::unique_lock<std::mutex> lock(mu);
        if (routines.size() == capacity)
        {
            routine->clear();
            delete routine;
            return false;
        }
        routines.push_front(routine);
        return true;
    }

}
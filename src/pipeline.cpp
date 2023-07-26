#include "pipeline.hpp"

namespace letMeSee
{
    void Pipeline::addLast(PipelineHandler *handler)
    {
        if (handler == nullptr)
        {
            return;
        }
        handlers.push_back(handler);
    }

    PipelineHandler *Pipeline::getNext()
    {
        if (!hasNext())
        {
            return nullptr;
        }
        currentIndex += 1;
        return handlers[currentIndex];
    }

    bool Pipeline::hasNext()
    {
        return currentIndex + 1 < handlers.size();
    }

    void Pipeline::reset()
    {
        currentIndex = -1;
    }
}
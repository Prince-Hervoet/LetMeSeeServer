#include "pipeline.hpp"

namespace letMeSee
{
    Handler *Pipeline::getNext()
    {
    }

    Handler *Pipeline::getNext()
    {
        if (!hasNext())
        {
            return nullptr;
        }
        cursor += 1;
        return handlers[cursor];
    }

    bool Pipeline::hasNext()
    {
        return !(cursor + 1 == handlers.size());
    }

    void Pipeline::addHandlerLast(Handler *handler)
    {
        handlers.push_back(handler);
    }

    int Pipeline::getSize()
    {
        return handlers.size();
    }
}
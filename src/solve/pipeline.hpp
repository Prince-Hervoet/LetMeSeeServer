#pragma once

#include <vector>

namespace letMeSee
{
    class Handler
    {
    public:
        virtual void handle() = 0;
    };

    class Pipeline
    {
    public:
        Handler *getNext();
        bool hasNext();
        void addHandlerLast(Handler *handler);
        int getSize();

    private:
        int cursor = -1;
        std::vector<Handler *> handlers;
    };
}
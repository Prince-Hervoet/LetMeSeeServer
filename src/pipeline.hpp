#pragma once

#include <vector>

namespace letMeSee
{
    class DataHandler
    {
        virtual void solve(int fd) = 0;
    };

    class PipelineHandler
    {
        virtual void solve(void *args) = 0;
    };

    class Pipeline
    {
    public:
        void addLast(PipelineHandler *handler);
        PipelineHandler *getNext();
        bool hasNext();
        void reset();

    private:
        int currentIndex = -1;
        std::vector<PipelineHandler *> handlers;
    };
}
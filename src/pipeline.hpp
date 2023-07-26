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
        PipelineHandler *getNext();
        bool hasNext();
        void reset();

    private:
        int currentIndex = 0;
        std::vector<PipelineHandler *> handlers;
    };
}
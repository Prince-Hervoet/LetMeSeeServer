#pragma once

#include <iostream>
#include <vector>

namespace letMeSee
{
    class WorkerNode
    {
        friend class WorkerHeap;

    public:
        size_t getWorkerId();
        float getScore();

    private:
        size_t workerId;
        float score;
    };

    class WorkerHeap
    {
    public:
        void push(size_t workerId, float score);
        WorkerNode *peek();
        WorkerNode *pop();
        int getSize();

    private:
        void heapify();
        void heapUp();
        std::vector<WorkerNode *> arr;
    };
}

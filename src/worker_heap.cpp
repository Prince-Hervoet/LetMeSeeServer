#include "worker_heap.hpp"

namespace letMeSee
{
    int WorkerHeap::getSize()
    {
        return arr.size();
    }

    WorkerNode *WorkerHeap::peek()
    {
        if (arr.size() == 0)
            return nullptr;
        return arr[0];
    }
}
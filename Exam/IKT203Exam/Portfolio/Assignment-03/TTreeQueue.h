#ifndef TQUEUE_H
#define TQUEUE_H
#define MAX_SIZE 200

#include <stdexcept>

#include "TBST.h"


template <typename T>
struct TTreeQueue {

    T* queue[MAX_SIZE];
    int head = 0;
    int tail = 0;
    int count = 0;


    TTreeQueue() = default;
    ~TTreeQueue() = default;

    void Enqueue(T* n)
    {
        if (n == nullptr)
            return;
        if (IsFull())
            throw std::overflow_error("Queue Overflow");
        queue[tail] = n;
        tail = (tail + 1) % MAX_SIZE;
        count++;
    }

    T* Dequeue()
    {
        if (IsEmpty())
            throw std::underflow_error("Empty Queue");
        T* n = queue[head];
        if (n == nullptr)
            return nullptr;
        head = (head + 1) % MAX_SIZE;
        count--;
        return n;
    }

    bool IsEmpty() const
    {
        return count == 0;
    }

    bool IsFull() const
    {
        return count == MAX_SIZE;
    }
};


#endif //TQUEUE_H
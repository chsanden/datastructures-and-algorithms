#include "TQueue.h"
#include <stdexcept>


// Time and space O(1) - only adds to the end of the queue and wraps around when needed
void TQueue::Enqueue(const int item)
{
    if (IsFull())
        throw std::overflow_error("Queue Overflow");
    queue[tail] = item;
    tail = (tail + 1) % MAX_SIZE;
    count++;
}

// Both O(1)
int TQueue::Dequeue()
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    const int item = queue[head];
    head = (head + 1) % MAX_SIZE;
    count--;
    return item;
}

// Both O(1)
int TQueue::Peek() const
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    return queue[head];
}

// Both O(1)
bool TQueue::IsEmpty() const
{
    return count == 0;
}

bool TQueue::IsFull() const
{
    return count == MAX_SIZE;
}

int TQueue::GetTail() const
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    return tail;
}






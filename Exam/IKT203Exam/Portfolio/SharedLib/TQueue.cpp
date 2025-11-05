#include "TQueue.h"

#include <stdexcept>


void TQueue::Enqueue(const std::string& text)
{
    if (IsFull())
        throw std::overflow_error("Queue Overflow");
    queue[tail] = text;
    tail = (tail + 1) % MAX_SIZE;
    count++;
}

std::string TQueue::Dequeue()
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    const std::string item = queue[head];
    head = (head + 1) % MAX_SIZE;
    count--;
    return item;
}

std::string TQueue::Peek() const
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    return queue[head];
}

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

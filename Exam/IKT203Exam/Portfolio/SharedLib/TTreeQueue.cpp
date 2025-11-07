#include "TTreeQueue.h"

#include <stdexcept>


void TTreeQueue::Enqueue(const std::string& text)
{
    if (IsFull())
        throw std::overflow_error("Queue Overflow");
    queue[tail] = text;
    tail = (tail + 1) % MAX_SIZE;
    count++;
}

std::string TTreeQueue::Dequeue()
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    const std::string item = queue[head];
    head = (head + 1) % MAX_SIZE;
    count--;
    return item;
}

std::string TTreeQueue::Peek() const
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    return queue[head];
}

bool TTreeQueue::IsEmpty() const
{
    return count == 0;
}

bool TTreeQueue::IsFull() const
{
    return count == MAX_SIZE;
}

int TTreeQueue::GetTail() const
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    return tail;
}

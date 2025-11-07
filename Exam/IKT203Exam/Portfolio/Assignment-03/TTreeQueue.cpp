#include "TTreeQueue.h"

#include <stdexcept>


void TTreeQueue::Enqueue(Node* n)
{
    if (n == nullptr)
        return;
    if (IsFull())
        throw std::overflow_error("Queue Overflow");
    queue[tail] = n;
    tail = (tail + 1) % MAX_SIZE;
    count++;
}

Node* TTreeQueue::Dequeue()
{
    if (IsEmpty())
        throw std::underflow_error("Empty Queue");
    Node* n = queue[head];
    if (n == nullptr)
        return nullptr;
    head = (head + 1) % MAX_SIZE;
    count--;
    return n;
}

bool TTreeQueue::IsEmpty() const
{
    return count == 0;
}

bool TTreeQueue::IsFull() const
{
    return count == MAX_SIZE;
}

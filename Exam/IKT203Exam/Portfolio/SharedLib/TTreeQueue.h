#ifndef TQUEUE_H
#define TQUEUE_H
#define MAX_SIZE 100

#include "TDoublyLinkedList.h"


// Circular array-based queue implementation.
// Used in Cat 1 to store print jobs (each job is a full document snapshot).
// Demonstrates FIFO behavior through enqueue/dequeue operations.
class TTreeQueue {
private:
    std::string queue[MAX_SIZE];
    int head = 0;
    int tail = 0;
    int count = 0;

public:
    TTreeQueue() = default;
    ~TTreeQueue() = default;

    void Enqueue(const std::string& text);          // Adds a new job at the tail of the queue.
    std::string Dequeue();                          // Removes and returns the next job in FIFO order.
    [[nodiscard]] int GetTail() const;
    [[nodiscard]] std::string Peek() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsFull() const;
};


#endif //TQUEUE_H
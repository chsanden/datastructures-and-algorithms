#ifndef TQUEUE_H
#define TQUEUE_H
#define MAX_SIZE 100

#include "TDoublyLinkedList.h"


class TQueue {
private:
    std::string queue[MAX_SIZE];
    int head = 0;
    int tail = 0;
    int count = 0;

public:
    TQueue() = default;
    ~TQueue() = default;

    void Enqueue(const std::string& text);
    std::string Dequeue();
    [[nodiscard]] int GetTail() const;
    [[nodiscard]] std::string Peek() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsFull() const;
};


#endif //TQUEUE_H
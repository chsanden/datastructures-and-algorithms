#ifndef STACKS_QUEUES_TQUEUE_H
#define STACKS_QUEUES_TQUEUE_H

#define MAX_SIZE (100 * 100)


class TQueue {
    private:
    int queue[MAX_SIZE] {};
    int head = 0;
    int tail = 0;
    int count = 0;

    public:
    TQueue() = default;
    ~TQueue() = default;

    void Enqueue(int item);
    int Dequeue();
    [[nodiscard]] int GetTail() const;
    [[nodiscard]] int Peek() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsFull() const;
};
#endif //STACKS_QUEUES_TQUEUE_H
#ifndef STACKS_QUEUES_TSTACK_H
#define STACKS_QUEUES_TSTACK_H

#define MAX_SIZE (100 * 100)


class TStack {
private:
    int stack[MAX_SIZE]{};
    int top = 0;

public:
    TStack() = default;
    ~TStack() = default;

    void Push(int item);
    [[nodiscard]] int Pop();
    [[nodiscard]] int Peek() const;
    [[nodiscard]] bool IsEmpty() const;

};

#endif //STACKS_QUEUES_TSTACK_H
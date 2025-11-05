#ifndef TSTACK_H
#define TSTACK_H

#define STACK_MAX_SIZE 100
#include <string>


enum EnumActionType {
    INSERT,
    DELETE
};

class TStack {
private:
    struct TAction {
        EnumActionType action;
        std::string text;
        int index;
    };

    TAction event[STACK_MAX_SIZE]{};
    int top = 0;

public:
    TStack() = default;
    ~TStack() = default;

    void Push(const TAction& action);
    TAction Pop();
    [[nodiscard]] TAction Peek() const;
    [[nodiscard]] bool IsEmpty() const;
    void Clear();

};


#endif //TSTACK_H
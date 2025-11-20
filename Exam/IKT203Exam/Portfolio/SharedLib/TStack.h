#ifndef TSTACK_H
#define TSTACK_H

#define STACK_MAX_SIZE 100
#include <string>


enum EnumActionType {
    INSERT,
    DELETE
};

// Simple fixed-size stack used for undo/redo.
// Stores actions describing line insert/delete operations.
class TStack {
private:
    // Describes a single text-edit action.
    // 'action' indicates INSERT or DELETE,
    // 'text' stores the affected line, and 'index' is the line position.
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
    void Push(const TAction& action);       // Adds a new action to the top of the stack.
    TAction Pop();                          // Removes and returns the most recent action.
    [[nodiscard]] TAction Peek() const;
    [[nodiscard]] bool IsEmpty() const;
    void Clear();

};


#endif //TSTACK_H
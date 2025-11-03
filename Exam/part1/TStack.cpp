#include "TStack.h"
#include <stdexcept>

void TStack::Push(const TAction& action)
{
    if (top >= STACK_MAX_SIZE)
        throw std::overflow_error("Stack overflow");
    event[top++] = action;
}

TStack::TAction TStack::Pop()
{
    if (top == 0)
        throw std::underflow_error("Stack empty");
    return event[--top];
}

TStack::TAction TStack::Peek() const
{
    if (top == 0)
        throw std::underflow_error("Stack empty");
    return event[top - 1];
}

bool TStack::IsEmpty() const
{
    return top == 0;
}

void TStack::Clear()
{
    for (int i = 0; i < top; i++) {
        this->Pop();
    }
}


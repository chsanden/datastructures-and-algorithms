#include "TStack.h"
#include <iostream>

// Time complexity O(1) - always append to the end of the array and use that as the top of the stack
// Space complexity O(1) - no need to save helper variables, just place on top of existing, size-static stack
void TStack::Push(const int item)
{
    if (top >= MAX_SIZE)
        throw std::overflow_error("Stack overflow");
    stack[top++] = item;
}


// Time and space complexity both O(1) - Only works with the top element so if you have
// 5 or 500 elements in the stack the result will be the same
// Only returns and removes top element
int TStack::Pop()
{
    if (top == 0)
        throw std::underflow_error("Stack underflow");
    return stack[--top];
}

// Time and space complexity O(1) - only returns the top element
int TStack::Peek() const
{
    if (top == 0)
        throw std::underflow_error("Stack underflow");
    return stack[top - 1];
}

// O(1) for both, checks to see if the stack is empty or not
// doesn't determine exact amount - just makes sure it has one
bool TStack::IsEmpty() const
{
    return top == 0;
}







#ifndef STACKS_QUEUES_FUTILS_H
#define STACKS_QUEUES_FUTILS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "TQueue.h"
#include "TStack.h"

constexpr int GRID_ROWS = 100;
constexpr int GRID_COLS = 100;


// Stack is perfect here because of the structure and behaviour of stacks - LIFO
// When we push the string in it will send the first char to the bottom of the stack
// When we push the string back out it will pop the last char first, then the second to last, then third and so on
// Time and space complexity is O(n) - each char pushed and popped exactly once and
// helper string "reverse clone" is needed for output
inline std::string ReverseString(const std::string& input)
{
    if (input.size() > MAX_SIZE)
        throw std::overflow_error("Input longer than MAX_SIZE");
    TStack s;
    for (char c : input)
        s.Push(c);
    std::string output;
    output.reserve(input.size());
    while (!s.IsEmpty())
    {
        output.push_back(s.Pop());
    }
    return output;
}

// Time = O(n) - push 2 .. n once and pop each once
// Space = O(1) - fixed size array inside TStack
inline long long Factorial(const int base)
{
    if (base < 0)
        throw std::invalid_argument("n must be >= 0");
    if (base == 0 || base == 1)
        return 1;
    if (base > MAX_SIZE)
        throw std::overflow_error("n exceeds MAX_SIZE");
    TStack s;
    for (int i = 2; i <= base; ++i)
        s.Push(i);
    long long result = 1;
    while (!s.IsEmpty())
        result *= s.Pop();
    return result;
}

// Time = O(arrivals + toServe)
// Space = O(1) - fixed size queue
inline void SimulateWaitLine(const int arrivals, int toServe, TQueue& queue)
{
    static int nextId = 1;
    // arrivals
    for (int i = 1; i <= arrivals; ++i) {
        queue.Enqueue(nextId);
        std::cout << "Arrives: " << nextId << std::endl;
        nextId++;
    }

    // served
    for (int i = 0; i < toServe && !queue.IsEmpty(); ++i) {
        std::cout << "Served: " << queue.Dequeue() << std::endl;
    }
}

// O(1) both - just checking if true or false
inline bool InBounds (int r, int c)
{
    return r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS;
}

// O(r * c)
inline void ResetVisited(bool visited[GRID_ROWS][GRID_COLS])
{
    for (int r = 0; r < GRID_ROWS; ++r) {
        for (int c = 0; c < GRID_COLS; ++c) {
            visited[r][c] = false;
        }
    }
}

inline int EncodePos(int r, int c) {
    return r * GRID_COLS + c;
}

inline void DecodePos(int code, int& r, int& c) {
    r = code / GRID_COLS;
    c = code % GRID_COLS;
}

// Time = O( r * c) worst case
// Space is O(1)
inline bool DFSFindZero(const int grid[GRID_ROWS][GRID_COLS], bool visited[GRID_ROWS][GRID_COLS],
                        int startR, int startC, int& outR, int& outC)
{
    TStack s;

    // mark start immediately to avoid multiple pushes
    visited[startR][startC] = true;
    s.Push(EncodePos(startR, startC));

    while (!s.IsEmpty())
    {
        int code = s.Pop();
        int r, c; DecodePos(code, r, c);

        if (grid[r][c] == 0) {
            outR = r; outC = c;
            return true;
        }

        // Push neighbours, marking visited when discovered
        if (InBounds(r - 1, c) && !visited[r - 1][c]) {
            visited[r - 1][c] = true;
            s.Push(EncodePos(r - 1, c)); // up
        }
        if (InBounds(r, c + 1) && !visited[r][c + 1]) {
            visited[r][c + 1] = true;
            s.Push(EncodePos(r, c + 1)); // right
        }
        if (InBounds(r + 1, c) && !visited[r + 1][c]) {
            visited[r + 1][c] = true;
            s.Push(EncodePos(r + 1, c)); // down
        }
        if (InBounds(r, c - 1) && !visited[r][c - 1]) {
            visited[r][c - 1] = true;
            s.Push(EncodePos(r, c - 1)); // left
        }
    }
    return false;
}

// Same complexity as DFS
inline bool BFSFindZero(const int grid[GRID_ROWS][GRID_COLS], bool visited[GRID_ROWS][GRID_COLS],
                        int startR, int startC, int& outR, int& outC)
{
    TQueue q;

    // mark start immediately to avoid duplicate enqueues
    visited[startR][startC] = true;
    q.Enqueue(EncodePos(startR, startC));

    while (!q.IsEmpty())
    {
        int code = q.Dequeue();
        int r, c; DecodePos(code, r, c);

        if (grid[r][c] == 0) {
            outR = r; outC = c;
            return true;
        }

        // Enqueue neighbours, marking visited on discovery
        if (InBounds(r - 1, c) && !visited[r - 1][c]) {
            visited[r - 1][c] = true;
            q.Enqueue(EncodePos(r - 1, c)); // up
        }
        if (InBounds(r, c + 1) && !visited[r][c + 1]) {
            visited[r][c + 1] = true;
            q.Enqueue(EncodePos(r, c + 1)); // right
        }
        if (InBounds(r + 1, c) && !visited[r + 1][c]) {
            visited[r + 1][c] = true;
            q.Enqueue(EncodePos(r + 1, c)); // down
        }
        if (InBounds(r, c - 1) && !visited[r][c - 1]) {
            visited[r][c - 1] = true;
            q.Enqueue(EncodePos(r, c - 1)); // left
        }
    }
    return false;
}




#endif //STACKS_QUEUES_FUTILS_H
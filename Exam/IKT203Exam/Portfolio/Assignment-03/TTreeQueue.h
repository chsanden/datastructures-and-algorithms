#ifndef TQUEUE_H
#define TQUEUE_H
#define MAX_SIZE 200

#include "TBST.h"



struct TTreeQueue {

    Node* queue[MAX_SIZE];
    int head = 0;
    int tail = 0;
    int count = 0;


    TTreeQueue() = default;
    ~TTreeQueue() = default;

    void Enqueue(Node* n);
    Node* Dequeue();
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] bool IsFull() const;
};


#endif //TQUEUE_H
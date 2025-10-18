#ifndef IKT203_TMOVIELIST_H
#define IKT203_TMOVIELIST_H

#include "TMovie.h"
#include "TMovieNode.h"

class TMovieList {
private:
    TMovieNode* head;
    TMovieNode* tail;

public:
    TMovieList() : head(new TMovieNode(nullptr)), tail(head) {}

    ~TMovieList()
    {
        TMovieNode* current = head;
        while(current)
        {
            TMovieNode* next = current->GetNextNode();
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    void Append(TMovie* m);
    void Prepend(TMovie* m);

    TMovieNode *NavigateToNode(int index);

    TMovie* GetAtIndex(int index);
    void Remove(int index);
};


#endif //IKT203_TMOVIELIST_H

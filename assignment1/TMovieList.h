#ifndef IKT203_TMOVIELIST_H
#define IKT203_TMOVIELIST_H

#include "TMovie.h"
#include "TMovieNode.h"

// typedef to increase flexibility and reduce code recycling
typedef bool (*FCheckMovie)(TMovie* movie, void* criteria);

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
    TMovie* SearchFor(FCheckMovie check_movie, void* criteria) const;

    [[nodiscard]] TMovieNode *NavigateToNode(int index) const;

    [[nodiscard]] TMovie* GetAtIndex(int index) const;
    void Remove(int index);
};


#endif //IKT203_TMOVIELIST_H

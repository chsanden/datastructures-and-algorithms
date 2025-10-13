#ifndef IKT203_TMOVIELIST_H
#define IKT203_TMOVIELIST_H

#include "TMovie.h"
#include "TMovieNode.h"



using namespace std;

class TMovieList {
private:
    TMovieNode* head;

public:
    TMovieList() : head(new TMovieNode(nullptr)) {}

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
    }

void PushFront(TMovie* m) const
  {
        auto* n = new TMovieNode(m);
        n->SetNextNode(head->GetNextNode());
        head->SetNextNode(n);
  }
};


#endif //IKT203_TMOVIELIST_H

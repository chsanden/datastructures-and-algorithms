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

};


#endif //IKT203_TMOVIELIST_H

#ifndef IKT203_TMOVIENODE_H
#define IKT203_TMOVIENODE_H

#include "TMovie.h"



using namespace std;



class TMovieNode {
private:

    TMovie* movie;
    TMovieNode* nextNode;

public:

    // constructor
    explicit TMovieNode(TMovie* moviePointer) : movie(moviePointer), nextNode(nullptr) {}

    // destructor
    ~TMovieNode()
    {
        delete movie;
        movie = nullptr;
    }

    // getter and setter for nextNode pointer
    TMovieNode* GetNextNode()
    {
        return nextNode;
    }

    void SetNextNode(TMovieNode* next)
    {
        nextNode = next;
    }

};



#endif //IKT203_TMOVIENODE_H

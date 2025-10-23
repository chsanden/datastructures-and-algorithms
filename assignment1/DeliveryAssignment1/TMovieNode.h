#ifndef IKT203_TMOVIENODE_H
#define IKT203_TMOVIENODE_H

#include "TMovie.h"

class TMovieNode {
private:

    TMovie* movie;
    TMovieNode* nextNode;
    TMovieNode* prevNode;

public:

    // constructor
    explicit TMovieNode(TMovie* moviePointer) : movie(moviePointer), nextNode(nullptr), prevNode(nullptr) {}

    // destructor
    ~TMovieNode()
    {
        delete movie;
        movie = nullptr;
    }

    // getters and setters for next and previous nodes
    [[nodiscard]] TMovieNode* GetNextNode() const
    {
        return nextNode;
    }

    void SetNextNode(TMovieNode* next)
    {
        nextNode = next;
    }

    [[nodiscard]] TMovieNode* GetPrevNode() const
    {
        return prevNode;
    }
    void SetPrevNode(TMovieNode* prev)
    {
        prevNode = prev;
    }
    [[nodiscard]] TMovie* GetMovie() const
    {
        return movie;
    }
};



#endif //IKT203_TMOVIENODE_H

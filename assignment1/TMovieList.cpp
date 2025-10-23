#include "TMovieList.h"

#include <iostream>

using namespace std;

void TMovieList::Append(TMovie* m)
{
    // Time complexity O(1) with using tail and prev nodes
    auto* newNode = new TMovieNode(m);
    newNode->SetPrevNode(tail);
    tail->SetNextNode(newNode);
    tail = newNode;
    cout << "Appended '" << m->GetTitle() << "' into existing list of movies" <<endl;
}

void TMovieList::Prepend(TMovie* m)
{
    auto* newNode = new TMovieNode(m);
    auto* old = head->GetNextNode();
    newNode->SetNextNode(head->GetNextNode());
    head->SetNextNode(newNode);

    newNode->SetPrevNode(head);
    if (old)
        old->SetPrevNode(newNode);

    cout << "Prepended '" << m->GetTitle() << "' into list of movies" <<endl;
    if (tail == head)
        tail = newNode;
}

TMovieNode* TMovieList::NavigateToNode(const int index) const
{
    // Negativ index finnes ikke -> ugyldig
    if (index < 0)
        return nullptr;

    auto* node = head->GetNextNode();
    int i = 0;
    while (node != nullptr && i < index)
    {
        node = node->GetNextNode();
        i++;
    }

    // Index større enn lista -> ugyldig
    if (node == nullptr)
        return nullptr;
    return node;

}

TMovie* TMovieList::GetAtIndex(const int index) const
{
    auto* node = NavigateToNode(index);
    return node ? node->GetMovie() : nullptr;
}

void TMovieList::Remove(const int index)
{
    auto* node = NavigateToNode(index);
    if (node == nullptr)
        return;

    auto* prev = node->GetPrevNode();
    auto* next = node->GetNextNode();

    if (prev)
        prev->SetNextNode(next);
    if (next)
        next->SetPrevNode(prev);
    else
        tail = (prev ? prev : head);


    if (head->GetNextNode() == nullptr)
        tail = head;

    delete node;
}

TMovie *TMovieList::SearchFor(const FCheckMovie check_movie, void *criteria) const
{
    auto* node = head->GetNextNode();
    while (node != nullptr)
    {
        if (check_movie(node->GetMovie(), criteria))
        {
            return node->GetMovie();
        }
        node = node->GetNextNode();
    }
    return nullptr;
}

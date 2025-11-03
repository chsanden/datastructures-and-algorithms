#include "TDoublyLinkedList.h"
#include <iostream>


void TDoublyLinkedList::Append(const std::string& line)
{
    auto* newNode = new Node(line);
    if (size == 0)
        head = tail = newNode;
    else {
        newNode->SetPrev(tail);
        tail->SetNext(newNode);
        tail = newNode;
    }
    size++;
}

void TDoublyLinkedList::Prepend(const std::string& line)
{
    auto* newNode = new Node(line);
    if (size == 0)
        head = tail = newNode;
    else {
        newNode->SetNext(head);
        head->SetPrev(newNode);
        head = newNode;
    }
    size++;
}

TDoublyLinkedList::Node* TDoublyLinkedList::NavigateToNode(const int index) const
{
    if (index < 0 || index >= size)
        return nullptr;

    auto* node = head;

    for (int i = 0; i < index; i++)
        node = node->GetNext();

    return node;
}

void TDoublyLinkedList::Remove(const int index)
{
    auto* node = NavigateToNode(index);
    if (!node)
        return;

    if (node->GetPrev())
        node->GetPrev()->SetNext(node->GetNext());
    else
        head = node->GetNext();
    if (node->GetNext())
        node->GetNext()->SetPrev(node->GetPrev());
    else
        tail = node->GetPrev();

    delete node;
    size--;
}

std::string TDoublyLinkedList::GetAtIndex(const int index) const
{
    const auto* node = NavigateToNode(index);
    return node ? node->GetLine() : "Error, line does not exist\n";
}

void TDoublyLinkedList::InsertAtIndex(const int index, const std::string &line)
{
    if (index < 0 || index > size) {
        std::cout << "========\nIndex doesn't exist\n========\n" << std::endl;
        return;
    }
    if (index == 0)
    {
        Prepend(line);
        return;
    }
    if (index == size)
    {
        Append(line);
        return;
    }
    Node* cur = head;
    for (int i = 0; i < index; i++)
        cur = cur->GetNext();
    Node* newNode = new Node(line);
    Node* prev = cur->GetPrev();

    newNode->SetPrev(prev);
    newNode->SetNext(cur);

    prev->SetNext(newNode);
    cur->SetPrev(newNode);

    size++;
}


int TDoublyLinkedList::GetSize() const
{
    return size;
}









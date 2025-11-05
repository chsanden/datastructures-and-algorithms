#ifndef TDOUBLYLINKEDLIST_H
#define TDOUBLYLINKEDLIST_H
#include <string>
#include <utility>
#include "SharedLib.h"



class TDoublyLinkedList {

private:
    struct Node {
        std::string line;
        Node* next;
        Node* prev;
        explicit Node(std::string  text) : line(std::move(text)), next(nullptr), prev(nullptr) {}

        void SetNext(Node* node)
        {
            this->next = node;
        }
        void SetPrev(Node* node)
        {
            this->prev = node;
        }
        [[nodiscard]] Node* GetPrev() const
        {
            return this->prev;
        }
        [[nodiscard]] Node* GetNext() const
        {
            return this->next;
        }
        [[nodiscard]] std::string GetLine() const
        {
            return line;
        }

    };

    Node* head;
    Node* tail;
    int size;


public:
    TDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~TDoublyLinkedList() = default;

    void Append(const std::string &line);
    void Prepend(const std::string& line);
    [[nodiscard]] Node* NavigateToNode(int index) const;
    void Remove(int index);
    [[nodiscard]] std::string GetAtIndex(int index) const;
    void InsertAtIndex(int index, const std::string &line);
    [[nodiscard]] int GetSize() const;
};


#endif //TDOUBLYLINKEDLIST_H
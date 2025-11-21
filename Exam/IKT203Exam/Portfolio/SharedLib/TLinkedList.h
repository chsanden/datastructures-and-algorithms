#ifndef IKT203_COURSE_ASSIGNMENTS_TLINKEDLIST_H
#define IKT203_COURSE_ASSIGNMENTS_TLINKEDLIST_H

#include "TPerson.h"

// Singly linked list of TPerson, used for the guest and employee manifests.
// Owns all its Node objects and frees them in the destructor.
// Supports append, prepend, insert, remove, indexed access, and merge-sort.
class TLinkedList {


    private:
    struct Node {
        TPerson person;  // stored by value
        Node* next;
        explicit Node(const TPerson& p) : person(p), next(nullptr) {}

        void setNext(Node* n)
        {
            this->next = n;
        }

        [[nodiscard]] static Node* GetNext(const Node* n)
        {
            return n->next;
        }

        [[nodiscard]] static TPerson GetPerson(Node* n)
        {
            return n->person;
        }
    };
    Node* head;
    Node* tail;
    int size;
public:
    TLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~TLinkedList();

    void Append(const TPerson& person);
    void Prepend(const TPerson& person);
    void InsertAtIndex(int index, const TPerson& person);
    void Remove(int index);
    [[nodiscard]] TPerson GetAtIndex(int index) const;
    [[nodiscard]] int GetSize() const { return size; }
    static void MergeSortSplit(Node* source, Node** front, Node** back);
    static Node* MergeList(Node*, Node*);
    static Node* MergeSort(Node*);
    void Sort();






};


#endif //IKT203_COURSE_ASSIGNMENTS_TLINKEDLIST_H
#include "TLinkedList.h"
#include <iostream>

TLinkedList::~TLinkedList()
{
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void TLinkedList::Append(const TPerson& person)
{
    Node* newNode = new Node(person);
    if (size == 0) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void TLinkedList::Prepend(const TPerson& person)
{
    Node* newNode = new Node(person);
    if (size == 0) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void TLinkedList::InsertAtIndex(const int index, const TPerson& person)
{
    if (index < 0 || index > size) {
        std::cout << "Index out of range\n";
        return;
    }

    if (index == 0) {
        Prepend(person);
        return;
    }
    if (index == size) {
        Append(person);
        return;
    }

    Node* prev = head;
    for (int i = 0; i < index - 1; ++i)
        prev = prev->next;

    Node* newNode = new Node(person);
    newNode->next = prev->next;
    prev->next = newNode;
    size++;
}

void TLinkedList::Remove(const int index)
{
    if (index < 0 || index >= size)
        return;

    if (index == 0) {
        const Node* oldHead = head;
        head = head->next;
        if (size == 1)
            tail = nullptr;
        delete oldHead;
        size--;
        return;
    }

    Node* prev = head;
    for (int i = 0; i < index - 1; ++i)
        prev = prev->next;

    const Node* toDelete = prev->next;
    prev->next = toDelete->next;
    if (toDelete == tail)
        tail = prev;
    delete toDelete;
    size--;
}

TPerson TLinkedList::GetAtIndex(const int index) const
{
    if (index < 0 || index >= size) {
        std::cout << "Index out of range\n";
        return {};
    }

    Node* cur = head;
    for (int i = 0; i < index; ++i)
        cur = cur->next;

    return cur->person;
}

void TLinkedList::MergeSortSplit(Node *source, Node **front, Node **back)
{
    if (source == nullptr || source->next == nullptr) {
        *front = source;
        *back = nullptr;
        return;
    }

    Node* slow = source;
    const Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

TLinkedList::Node *TLinkedList::MergeList(Node *a, Node *b)
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;

    Node* result = nullptr;

    if (a->person < b->person) {
        result = a;
        result->next = MergeList(a->next, b);
    }
    else {
        result = b;
        result->next = MergeList(a, b->next);
    }
    return result;
}

/// Time complexity O(n log n) at all times
/// Does NOT sort in place, so more memory is needed to complete
TLinkedList::Node *TLinkedList::MergeSort(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* front;
    Node* back;

    MergeSortSplit(head, &front, &back);

    front = MergeSort(front);
    back = MergeSort(back);
    return MergeList(front, back);
}

void TLinkedList::Sort()
{
    this->head = MergeSort(head);

    Node* cur = this->head;
    tail = nullptr;
    while (cur) {
        if (cur->next == nullptr)
            tail = cur;
        cur = cur->next;
    }
}
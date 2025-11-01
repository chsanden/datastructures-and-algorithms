#ifndef SIMPLESEARCH_TLINKEDLIST_H
#define SIMPLESEARCH_TLINKEDLIST_H
#include "TBankAccount.h"
#include "FCompareAccount.h"
#include "SearchSummary.h"


// Using singly linked list since we gain very little in terms of functionality when going for doubly or circular
// and singly is a lot leaner when it comes to space complexity

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
    explicit Node(T v) : value(v), next(nullptr) {}
};

template <typename T>
class TLinkedList {
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    bool ownsData = false;
    std::size_t listSize = 0;

    public:
    explicit TLinkedList(bool owns) : ownsData(owns) {}
    ~TLinkedList()
    {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            if (ownsData)
                delete current->value;
            delete current;
            current = next;
        }
    }

    [[nodiscard]] size_t Size() const;
    [[nodiscard]] bool Empty() const;
    void PushBack(T v);

    template <typename Pred>
    T FindIf(Pred p) const
    {
        for (auto* n = head; n; n = n->next)
            if (p(n->value))
                return n->value;
        return nullptr;
    }

    template <typename Pred>
    bool RemoveIf(Pred p)
    {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        while (current) {
            if (p(current->value)) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;
                if (ownsData)
                    delete current->value;
                delete current;
                --listSize;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    TBankAccount* Find(FCompareAccount onCompare, void* searchKey, SearchSummary* summary) const;
    TLinkedList<TBankAccount*>* Every(FCompareAccount onCompare, void* searchKey, SearchSummary* summary) const;

};


#endif //SIMPLESEARCH_TLINKEDLIST_H

#include <chrono>

template<typename T>
TBankAccount *TLinkedList<T>::Find(FCompareAccount onCompare, void *searchKey, SearchSummary *summary) const
{
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    if (!onCompare)
        return nullptr;
    for (auto* n = head; n; n = n->next) {
        ++summary->comparisons;
        if (onCompare(n->value, searchKey)) {
            auto elapsed = clock::now() - start;
            summary->timeSpentMs = std::chrono::duration<double, std::milli>(elapsed).count();
            return n->value;
        }
    }
    auto elapsed = clock::now() - start;
    summary->timeSpentMs = std::chrono::duration<double, std::milli>(elapsed).count();
    return nullptr;
}

template<typename T>
TLinkedList<TBankAccount *> *TLinkedList<T>::Every(FCompareAccount onCompare, void *searchKey, SearchSummary *summary) const
{
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    auto* result = new TLinkedList<TBankAccount*>(false);
    if (!onCompare) {
        auto elapsed = clock::now() - start;
        summary->timeSpentMs = std::chrono::duration<double, std::milli>(elapsed).count();
        return result;
    }
    for (auto* n = head; n; n = n->next) {
        ++summary->comparisons;
        if (onCompare(n->value, searchKey)) {
            result->PushBack(n->value);
        }
    }
    auto elapsed = clock::now() - start;
    summary->timeSpentMs = std::chrono::duration<double, std::milli>(elapsed).count();
    return result;
}

template<typename T>
size_t TLinkedList<T>::Size() const
{
    return listSize;
}

template<typename T>
bool TLinkedList<T>::Empty() const
{
    return listSize == 0;
}

template<typename T>
void TLinkedList<T>::PushBack(T v)
{
    auto* n = new Node<T>(v);
    if (!tail)
        head = tail = n;
    else {
        tail->next = n;
        tail = n;
    }
    listSize++;
}







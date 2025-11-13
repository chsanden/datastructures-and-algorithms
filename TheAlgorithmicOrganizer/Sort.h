#pragma once
#include "BankAccount.h"
#include "BankAccountList.h"

typedef int (*FCompareAccounts)(TBankAccount* a, TBankAccount* b);

struct OperationSummary {
    long long comparisons = 0;
    long long swaps = 0;
    double timeSpentInMs = 0.0;

    void Reset()
    {
        comparisons = 0;
        swaps = 0;
        timeSpentInMs = 0.0;
    }
};

class Sort {
public:
    Sort(TBankAccount** sourceArray, int count, TLinkedList* sourceList);

    TBankAccount** GetArray() const
    {
        return m_array;
    }
    int GetCount() const
    {
        return m_count;
    }
    TLinkedList* GetList() const
    {
        return m_list;
    }

    TBankAccount** CloneArray() const;
    TLinkedList* CloneList() const;

    TBankAccount** SelectionSortArray(FCompareAccounts cmp, OperationSummary& out);
    TLinkedList*   SelectionSortList(FCompareAccounts cmp, OperationSummary& out);
    TBankAccount** BubbleSortArray(FCompareAccounts cmp, OperationSummary& out);
    TBankAccount** QuickSortArray(FCompareAccounts cmp, OperationSummary& out);
    TLinkedList*   MergeSortList(FCompareAccounts cmp, OperationSummary& out);



private:
    TBankAccount** m_array = nullptr;
    int m_count = 0;
    TLinkedList* m_list = nullptr;

};
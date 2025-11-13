#include "Sort.h"

int CompareByLastName(const TBankAccount* a, const TBankAccount* b)
{
    if (a == b)
        return 0;
    if (!a)
        return -1;
    if (!b)
        return 1;

    if (a->ownerLastName < b->ownerLastName)
        return -1;
    if (a->ownerLastName > b->ownerLastName)
        return 1;
    if (a->ownerFirstName < b->ownerFirstName)
        return -1;
    if (a->ownerFirstName > b->ownerFirstName)
        return 1;
    return 0;
}

int CompareByBalanceAsc(const TBankAccount* a, const TBankAccount* b)
{
    if (a == b)
        return 0;
    if (!a)
        return -1;
    if (!b)
        return 1;

    if (a->getBalance() < b->getBalance())
        return -1;
    if (a->getBalance() > b->getBalance())
        return 1;
    return 0;
}

static int CmpWrap(FCompareAccounts cmp, TBankAccount* a, TBankAccount* b, OperationSummary& s)
{
    ++s.comparisons;
    return cmp(a, b);
}

static void SwapPointers(TBankAccount* a, TBankAccount* b, OperationSummary* s)
{
    std::swap(a, b);
    ++s->swaps;
}

Sort::Sort(TBankAccount **sourceArray, int count, TLinkedList *sourceList)
: m_array(sourceArray), m_count(count), m_list(sourceList){}

TBankAccount **Sort::CloneArray() const
{
    if (!m_array || m_count == 0)
        return nullptr;
    auto** copy = new TBankAccount*[m_count];
    for (int i = 0; i < m_count; i++)
        copy[i] = m_array[i];
    return copy;
}

static TLinkedList* g_cloneTarget = nullptr;

static void AppendToClone(TBankAccount* acc, int)
{
    if (g_cloneTarget)
        g_cloneTarget->Append(acc);
}

TLinkedList *Sort::CloneList() const
{
    if (!m_list)
        return nullptr;
    auto* copy = new TLinkedList(false);
    m_list->forEach(AppendToClone);
    g_cloneTarget = copy;
    return copy;
}



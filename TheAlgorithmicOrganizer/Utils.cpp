#include <bits/stl_tree.h>

#include "SharedLib.h"
int g_printIndex = 0;

static void PrintAccCallback(TBankAccount* acc, int /*i*/)
{
    std::cout << g_printIndex++ << ": " << acc->ownerFirstName << " " << acc->ownerLastName
    << " | Balance: " << acc->getBalance() << std::endl;
}

void PrintList(TLinkedList* list)
{
    if (!list)
        return;
    g_printIndex = 0;
    list->forEach(PrintAccCallback);
}
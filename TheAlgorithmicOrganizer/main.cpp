#include "main.h"
#include "SharedLib.h"


static TLinkedList g_list(false);
static std::vector<TBankAccount*> g_array;

static bool onNameRead(const int idx, const int total, const std::string& first, const std::string& last)
{
    auto* acc = new TBankAccount(EBankAccountType::Checking, first, last);

    g_list.Append(acc);
    g_array.push_back(acc);
    return true;
}

int main()
{
    readNamesFromFile("random_names.txt", onNameRead);

    Sort sorter(g_array.data(), (int)g_array.size(), &g_list);



    return 0;
}
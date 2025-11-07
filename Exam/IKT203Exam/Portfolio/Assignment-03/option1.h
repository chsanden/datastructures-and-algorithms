#pragma once

#ifndef OPTION1_H
#define OPTION1_H


#include <iostream>
#include <TTreeQueue.h>
#include <unordered_set>

#include "TBST.h"
#include "TEmployee.h"
#include "Utils.h"
#include "../../Submissions/Submission-04/BankAccount.h"

/// To keep track of used ID values to ensure
/// all unique IDs
inline std::unordered_set<int> usedIds;
static TBST* bst;

int RunApp();

inline void IdGenerator(TEmployee* employee)
{
    int id = Utils::RandomInt(1, 1000);

    while (usedIds.count(id) > 0)
        id = Utils::RandomInt(1, 1000);

    usedIds.insert(id);
    employee->id = id;
}
static bool onNameRead(const int index, const int aTotalCount, const std::string& aFirstName, const std::string& aLastName)
{
    const auto e = new TEmployee(aFirstName, aLastName);
    if (index >= 200)
        return false;
    IdGenerator(e);
    bst->Insert(e->id, e);

    std::cout << "[" << e->id << "] " << e->firstName << ", " << e->lastName << std::endl;

    return true;
}

inline void printline()
{
    std::cout << "----------------------------------------" << std::endl;
}

inline void pack(const std::string& line)
{
    std::cout << "\n\n\n" << std::endl;
    printline();
    std::cout << line << std::endl;
    printline();
}

#endif // OPTION1_H

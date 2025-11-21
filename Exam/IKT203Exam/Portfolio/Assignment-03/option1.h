#pragma once

#ifndef OPTION1_H
#define OPTION1_H

#include <iostream>
#include <unordered_set>
#include "TAVL.h"
#include "TBST.h"
#include "TEmployee.h"
#include "Utils.h"

// Global state for Category 3, Option 1:
// - bst: owns all TEmployee objects (deleted in TBST destructor)
// - avl: separate AVL tree used only to demonstrate balancing on int keys
inline std::unordered_set<int> usedIds;
static TBST* bst;
static TAVL* avl;

int RunApp();

// Assign a unique random employee ID in the range [1, 1000].
// Uses 'usedIds' to avoid duplicates so the BST always has unique keys.
inline void IdGenerator(TEmployee* employee)
{
    int id = Utils::RandomInt(1, 1000);

    while (usedIds.count(id) > 0)
        id = Utils::RandomInt(1, 1000);

    usedIds.insert(id);
    employee->id = id;
}

// Callback used by readNamesFromFile.
// - Creates a new TEmployee from the given name.
// - Stops after 200 employees (as required by the assignment).
// - Generates a unique ID and inserts the employee into the BST.
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

// Helper to visually separate different demos (traversals, search, etc.) in the console output.
inline void pack(const std::string& line)
{
    std::cout << "\n\n\n" << std::endl;
    printline();
    std::cout << line << std::endl;
    printline();
}



#endif // OPTION1_H

// option1.h : Option 1 (Standard): Console Text Editor.

#pragma once

#ifndef OPTION1_H
#define OPTION1_H
#include "TLinkedList.h"
#include "TPerson.h"

inline TLinkedList g, e;
inline int guestCount, employCount = 0;



int RunApp();


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
    std::cout << "\n\n\n" << std::endl;
}

/**
 * @brief Callback function to process one name.
static bool NameReadCallback(const int aIndex, const int aTotalCount, const std::string& aFirstName, const std::string& aLastName)
{
    std::cout << "Reading Name " << (aIndex + 1) << " of " << aTotalCount << ": "
        << aFirstName << " " << aLastName << "\n";

    // We only want to read 10 names (index 0 through 9)
    // Return false when aIndex is 9 to stop the loop after this one.
    return (aIndex < 9);
}
*/

// *Inspired* by the provided NameReadCallback given above
static bool onNameRead(const int aIndex, const int aTotalCount, const std::string& aFirstName, const std::string& aLastName)
{
    const ENumStatus status = (aIndex < 1500) ? EMPLOYEE : GUEST;

    const TPerson p(aFirstName, aLastName, status);


    if (status == EMPLOYEE) {
        e.Append(p);
        employCount++;
    }
    else {
        g.Append(p);
        guestCount++;
    }

    std::cout << "[" <<aIndex << "] " << aLastName << ", " << aFirstName << " | status: " << (status == 1 ? "Employee" : "Guest")
    << " | cabin size: " << p.cabinSize << std::endl;
    return true;
}


inline void SearchAndPrint(TPerson** targetArray, int arraySize, const std::string& target)
{
    int index = Utils::BinarySearch(targetArray, 0, arraySize - 1, target);
    
    if (index == -1) {
        std::cout << "No match found" << std::endl;
        return;
    }

    int left = index - 1;
    int right = index + 1;

    while (left >= 0 && (targetArray[left]->firstName == target || targetArray[left]->lastName == target)) {
        --left;
    }

    while (right < arraySize && (targetArray[right]->firstName == target || targetArray[right]->lastName == target)) {
        ++right;
    }

    for (int i = left + 1; i < right; ++i) {
        std::cout << "Match found: \nName: " << targetArray[i]->firstName << " "
                << targetArray[i]->lastName << " | status: " << (targetArray[i]->status == 0 ? "Guest" : "Employee")
                << " | cabinsize: " << targetArray[i]->cabinSize << "\n" << std::endl;
    }
}







#endif // OPTION1_H

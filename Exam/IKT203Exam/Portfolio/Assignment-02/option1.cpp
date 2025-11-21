#include <iostream>
#include <string>
#include "option1.h"
#include <limits>
#include "SharedLib.h"
#include "TLinkedList.h"
#include "TPerson.h"

// Entry point for Category 2, Option 1 (Cruise Ship Manifest).
// Steps:
// 1) Load names from DATA/random_names.txt into employee and guest lists
// 2) Merge-sort both lists alphabetically (lastName, firstName)
// 3) Convert guests to an array and quick-sort by cabinSize, then lastName
// 4) Allow the user to search (binary search) by surname in the chosen list
int RunApp()
{
    // Path to the names data file.
    // IMPORTANT: working directory must be set so that "DATA/random_names.txt" resolves correctly.
	const std::string filename = "DATA/random_names.txt";

    pack("Reading names and grouping them.");
	// Call the utility function with the name callback
	readNamesFromFile(filename, onNameRead);
    pack("Finished reading names.");

    /////////////////////////// Merge sorting ///////////////////////////
    // Sort both employee and guest linked lists alphabetically
    // using the linked-list merge sort implementation in TLinkedList.
    e.Sort();
    g.Sort();
    pack("Sorting.");
    // Attempt at "beautifying" the terminal output somewhat
    pack("Employees merge sorted alphabetically.");
    const int employeeSize = e.GetSize();
    auto** employeeAlphaSort = new TPerson*[employeeSize];
    printline();
    for (int i = 0; i < e.GetSize(); i++) {
        std::cout << "[" << i << "] " << e.GetAtIndex(i).lastName << ", " << e.GetAtIndex(i).firstName
        << " | status: Employee | cabin size: " << e.GetAtIndex(i).cabinSize << std::endl;
       employeeAlphaSort[i] = new TPerson(e.GetAtIndex(i));
    }
    printline();
    pack("Guests merge sorted alphabetically.");
    const int guestSize = g.GetSize();
    auto** guestAlphaSort = new TPerson*[guestSize];
    printline();
    for (int i = 0; i < g.GetSize(); i++) {
        std::cout << "[" << i << "] " << g.GetAtIndex(i).lastName << ", " << g.GetAtIndex(i).firstName
        << " | status: Guest | cabin size: " << g.GetAtIndex(i).cabinSize << std::endl;
        guestAlphaSort[i] = new TPerson(g.GetAtIndex(i));
    }
    printline();

    /////////////////////////// Quick sorting ///////////////////////////
    // Build an array of guests and quick-sort it by:
    // 1) cabinSize (ascending), then 2) lastName.
    // This array is used to optimise cabin assignment.
    // creating array from guest linked list
    auto** guestList = new TPerson*[guestCount];
    for (int i = 0; i < guestCount; i++) {
        guestList[i] = new TPerson(g.GetAtIndex(i));
    }
    Utils::QuickSort(guestList, 0, guestCount - 1);

    pack("Guests quick sorted by 1) cabinsize, 2) lastname.");
    printline();
    for (int i = 0; i < guestCount; i++) {
        std::cout << "[" << i << "] " << guestList[i]->lastName << ", " << guestList[i]->firstName
        << " | cabinSize: " << guestList[i]->cabinSize << std::endl;
    }
    printline();

    /////////////////////////// Binary search ///////////////////////////
    // Let the user choose whether to search employees or guests,
    // then perform binary search on the corresponding alphabetically
    // sorted array and print all matches with that surname.
    int choice;
    std::string target;
    std::cout << "What list do you want to search through: \n [1] Employee\n [2] Guest" << std::endl;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter name to search for: " << std::endl;
    std::getline(std::cin, target);

switch (choice) {
    case 1: SearchAndPrint(employeeAlphaSort, employCount, target); break;

    case 2: SearchAndPrint(guestAlphaSort, guestCount, target); break;

    default: {
        std::cout << "Choice invalid" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

    /////////////////////////// Cleanup before exit ///////////////////////////
    // Delete all dynamically allocated TPerson objects from:
    // - alphabetical employee array
    // - alphabetical guest array
    // - quick-sorted guestList array
    // Then clear the linked lists to avoid memory leaks.

    for (int i = 0; i < employeeSize; ++i)
        delete employeeAlphaSort[i];
    delete[] employeeAlphaSort;

    for (int i = 0; i < guestSize; ++i)
        delete guestAlphaSort[i];
    delete[] guestAlphaSort;

    for (int i = 0; i < guestCount; ++i)
        delete guestList[i];
    delete[] guestList;

    while (e.GetSize() > 0)
        e.Remove(0);
    while (g.GetSize() > 0)
        g.Remove(0);

    pack("Cleaned up memory");
    return 0;

}
// Option 1 (Standard): Console Text Editor.
//

#include <iostream>
#include <string>
#include "option1.h"

#include <limits>

#include "SharedLib.h"
#include "TLinkedList.h"
#include "TPerson.h"

// Assignment specific helpers in option1.h


int RunApp()
{
	/* Path to the names data file
    This is MY absolute path -- change to your local path for this to read properly
    something like "C:\Users\Username\FolderYouSavedTheSubmissionIn\Exam\IKT203Exam\DATA\random_names.txt"
    Double slash is needed for string to pass the correct file path */
	const std::string filename = "C:\\Users\\csand\\IKT203\\Exam\\IKT203Exam\\DATA\\random_names.txt";

    pack("Reading names and grouping them.");
	// Call the utility function with the name callback
	readNamesFromFile(filename, onNameRead);

    pack("Finished reading names.");




    /////////////////////////// Merge sorting ///////////////////////////
    e.Sort();
    g.Sort();
    pack("Sorting.");
    // Attempt at "beautifying" the terminal output somewhat
    pack("Employees merge sorted alphabetically.");
    TPerson* employeeAlphaSort[e.GetSize()];
    printline();
    for (int i = 0; i < e.GetSize(); i++) {
        //std::cout << "[" << i << "] " << e.GetAtIndex(i).lastName << ", " << e.GetAtIndex(i).firstName
       //<< " | status: Employee | cabin size: " << e.GetAtIndex(i).cabinSize << std::endl;
       employeeAlphaSort[i] = new TPerson(e.GetAtIndex(i));
    }
    printline();
    pack("Guests merger sorted alphabetically.");
    TPerson* guestAlphaSort[g.GetSize()];
    printline();
    for (int i = 0; i < g.GetSize(); i++) {
        //std::cout << "[" << i << "] " << g.GetAtIndex(i).lastName << ", " << g.GetAtIndex(i).firstName
       //<< " | status: Guest | cabin size: " << g.GetAtIndex(i).cabinSize << std::endl;
        guestAlphaSort[i] = new TPerson(g.GetAtIndex(i));
    }
    printline();



    /////////////////////////// Quick sorting ///////////////////////////
    // creating array from guest linked list
    auto** guestList = new TPerson*[guestCount];
    for (int i = 0; i < guestCount; i++) {
        guestList[i] = new TPerson(g.GetAtIndex(i));
    }
    // Quicksorting the guestlist array
    Utils::QuickSort(guestList, 0, guestCount - 1);

    pack("Guests quick sorted by 1) cabinsize, 2) lastname.");
    printline();
    for (int i = 0; i < guestCount; i++) {
        std::cout << "[" << i << "] " << guestList[i]->lastName << ", " << guestList[i]->firstName
        << " | cabinSize: " << guestList[i]->cabinSize << std::endl;
    }
    printline();







    /////////////////////////// Binary search ///////////////////////////
    int choice;
    std::string target;
    std::cout << "What list do you want to search through: \n [1] Employee\n [2] Guest" << std::endl;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter surname to search: " << std::endl;
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
    for (int i = 0; i < guestCount; i++) {
        delete guestList[i];
    }
    delete[] guestList;
    while (e.GetSize() > 0)
        e.Remove(0);
    while (g.GetSize() > 0)
        g.Remove(0);
    pack("Cleaned up memory");
	return 0;
}
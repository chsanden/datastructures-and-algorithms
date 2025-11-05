// Option 1 (Standard): Console Text Editor.
//

#include <iostream>
#include <string>
#include "option1.h"
#include "SharedLib.h"
#include "TLinkedList.h"
#include "TPerson.h"

TLinkedList g, e;

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
static bool onNameRead(const int aIndex, int aTotalCount, const std::string& aFirstName, const std::string& aLastName)
{
    const ENumStatus status = (aIndex < 1500) ? EMPLOYEE : GUEST;

    const TPerson p(aFirstName, aLastName, status);


    if (status == EMPLOYEE)
        e.Append(p);
    else
        g.Append(p);

    std::cout << "[" <<aIndex << "] " << aLastName << ", " << aFirstName << " | status: " << (status == 1 ? "Employee" : "Guest")
    << " | cabin size: " << p.cabinSize << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    return true;
}


int RunApp()
{
	/* Path to the names data file
    This is MY absolute path -- change to your local path for this to read properly
    something like "C:\Users\Username\FolderYouSavedTheSubmissionIn\Exam\IKT203Exam\DATA\random_names.txt"
    Double slash is needed for string to pass the correct file path */
	const std::string filename = "C:\\Users\\csand\\IKT203\\Exam\\IKT203Exam\\DATA\\random_names.txt";

	std::cout << "Reading names and grouping them: " << "\n" << std::endl;

	// Call the utility function with the name callback
	readNamesFromFile(filename, onNameRead);

	std::cout << "\nFinished reading names.\n\nSorting." << std::endl;

    // Merge sorting
    e.Sort();
    g.Sort();

    // Attempt at "beautifying" the terminal output somewhat
    std::cout << "\n\n\n---------------------------------------------------------------" << std::endl;
    std::cout << "Employees merge sorted alphabetically" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;


    for (int i = 0; i < e.GetSize(); i++) {
        std::cout << "[" << i << "] " << e.GetAtIndex(i).lastName << ", " << e.GetAtIndex(i).firstName
       << " | status: Employee | cabin size: " << e.GetAtIndex(i).cabinSize << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
    }

    std::cout << "\n\n\n---------------------------------------------------------------" << std::endl;
    std::cout << "Guests merger sorted alphabetically" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;


    for (int i = 0; i < g.GetSize(); i++) {
        std::cout << "[" << i << "] " << g.GetAtIndex(i).lastName << ", " << g.GetAtIndex(i).firstName
       << " | status: Guest | cabin size: " << g.GetAtIndex(i).cabinSize << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
    }

	return 0;
}
#include "Utils.h"
#include "TDoublyLinkedList.h"
#include "TStack.h"
#include "TPerson.h"
#include <ctime>
#include <iostream>
#include <limits>
#include <numbers>

int Utils::Choice()
{
    std::cout << "========\n1. Add line\n2. Remove line\n3. Print current document\n4. Print queue\n5. Undo\n6. Redo\n0. Exit"
                 "\n\nChoice:  ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

int Utils::Insert(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index)
{
        for (int i = 0; i < document.GetSize(); i++) {
        std::cout << i + 1 << ". " << document.GetAtIndex(i) << std::endl;
    }
    if (document.GetSize() > 0)
    {
        std::cout << "Enter the line number where you want to insert the line" <<std::endl;
        if (!(std::cin >> index)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "========\nIndex must be a number\n========\n\n" << std::endl;
            return index;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (document.GetSize() < 1)
        index = 1;

    std::cout << "Enter the text" <<std::endl;
    std::string line;
    std::getline(std::cin, line);


    document.InsertAtIndex(index - 1, line);
    undoStack.Push({INSERT, line, index - 1});
    if (!redoStack.IsEmpty()) {
        redoStack.Clear();
    }
    return index;
}

void Utils::PrintList(const TDoublyLinkedList &document)
{
    for (int i = 0; i < document.GetSize(); i++) {
        std::cout << i + 1 << ". " << document.GetAtIndex(i) << std::endl;
    }
    std::cout << "\n\n";
}

int Utils::RemoveLine(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index)
{
    std::cout << "Enter the number of the line you want to remove" <<std::endl;
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "========\nIndex must be a number\n========\n\n" << std::endl;
        return index;
    }    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    const std::string deletedLine = document.GetAtIndex(index-1);
    document.Remove(index-1);
    undoStack.Push({DELETE, deletedLine, index-1});
    if (!redoStack.IsEmpty()) {
        redoStack.Clear();
    }
    return index;
}

int Utils::RandomInt(const int min, const int max)
{
    static bool isSeeded = false;
    if (!isSeeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));      //<---- not the "best" random seeding available
        isSeeded = true;                                            // but sufficient for this use case
    }

    if (max <= min)
        return 0;

    return min + rand() % (max - min + 1);                          // <---- Limited randomness, but again
}                                                                   // sufficient for this use case

bool Utils::CompareLastnames(const TPerson *a, const TPerson *b)
{
    if (a->cabinSize < b->cabinSize)
        return true;
    if (a->cabinSize > b->cabinSize)
        return false;
    return a->lastName < b->lastName;
}


int Utils::Partition(TPerson **arr, const int startIndex, const int endIndex)
{
    TPerson *pivot = arr[endIndex];
    int i = startIndex - 1;

    for (int j = startIndex; j < endIndex; j++) {
        if (CompareLastnames(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }


    std::swap(arr[i + 1], arr[endIndex]);
    return i + 1;
}

/// Time complexity **on average** is O(n log n) but worst case it O(n^2)
/// depending on where in the range the pivot lands -- If pivot is at either extreme
/// the algorithm has to search through the entire list for every value it sorts -- n^2
/// However it does sort in-place, meaning no extra memory is needed
void Utils::QuickSort(TPerson** arr, const int low, const int high)
{
    if (low < high) {
        int p = Partition(arr, low, high);
        QuickSort(arr, low, p - 1);
        QuickSort(arr, p + 1, high);
    }
}

/// Time complexity of the binary search is O(log n)
/// However the included fallback search is O(n)
int Utils::BinarySearch(TPerson** arr, int p1, int p2, const std::string &target)
{
    const int origStart = p1;
    const int origEnd = p2;


    while (p1 <= p2) {
        const int newP = (p1 + p2) / 2;
        std::string currentFirst = arr[newP]->firstName;
        std::string currentLast = arr[newP]->lastName;

        if (target == currentFirst || target == currentLast)
            return newP;

        if (target > currentLast)
            p1 = newP + 1;

        else
            p2 = newP - 1;
    }

    /// Extra to search for firstname in the event that no matches were found
    /// Disregard this section if you're purely looking at the
    /// binary search understanding and implementation
    for (int i = origStart; i <= origEnd; i++) {
        if (arr[i]->firstName == target)
            return i;
    }
    return -1;
}
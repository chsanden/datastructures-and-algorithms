#include "Utils.h"

#include <iostream>
#include <limits>

#include "TDoublyLinkedList.h"
#include "TStack.h"


int Utils::Choice()
{
    std::cout << "========\n1. Add line\n2. Remove line\n3. Print current document\n4. Print queue\n5. Undo\n6. Redo\n0. Exit"
                 "\n\nChoice:  ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //std::cout << "\n=====================\n";
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

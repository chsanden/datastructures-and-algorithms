// Option 1 (Standard): Console Text Editor.
//

#include "option1.h"
#include <iostream>
#include "TDoublyLinkedList.h"
#include "TTreeQueue.h"
#include "TStack.h"
#include "Utils.h"

TDoublyLinkedList document;
TTreeQueue printQueue;
TStack undoStack, redoStack;

bool running = true;
int lastIndex = 0;
std::string deletedLine;

void Undo()
{
    if (!undoStack.IsEmpty()) {
        const auto action = undoStack.Pop();
        if (action.action == INSERT){
            document.Remove(action.index);
        }
        else{
            document.InsertAtIndex(action.index, action.text);
        }
        redoStack.Push(action);
    }
}
void Redo()
{
    if (!redoStack.IsEmpty()) {
        const auto action = redoStack.Pop();
        if (action.action == INSERT) {
            document.InsertAtIndex(action.index, action.text);
        }
        else {
            document.Remove(action.index);
        }
        undoStack.Push(action);
    }
}


int RunApp()
{
    // Implement the Console Text Editor application logic here
    while (running) {
        switch (Utils::Choice()) {
            case 1: {
                std::cout << "----------Add line----------" << std::endl;
                lastIndex = Utils::Insert(document, undoStack, redoStack, lastIndex);
                break;
            }
            case 2: {
                std::cout << "----------Remove line----------" << std::endl;
                Utils::PrintList(document);
                lastIndex = Utils::RemoveLine(document, undoStack, redoStack, lastIndex);
                break;
            }
            case 3: {
                std::cout << "----------Current document----------" << std::endl;
                for (int i = 0; i < document.GetSize(); i++)
                    std::cout << i + 1 << ". " << document.GetAtIndex(i) << std::endl;
                std::cout << "------------------------------------\n\n";
                break;
            }
            case 4: {
                for (int i = 0; i < document.GetSize(); ++i)
                    printQueue.Enqueue(document.GetAtIndex(i));

                std::cout << "----------Printing queue-----------" << std::endl;

                while (!printQueue.IsEmpty())
                    std::cout << printQueue.Dequeue() << std::endl;
                std::cout << "------------------------------------\n\n";

                    break;
                }

                case 5: {
                    std::cout << "----------UNDO----------" <<std::endl;
                    Undo();
                    break;
                }

                case 6: {
                    std::cout << "----------REDO----------" <<std::endl;
                    Redo();
                    break;
                }

                case 0: {
                    std::cout << "----------Exiting...----------" << std::endl;
                    running = false;
                break;
                }
                default: {
                    std::cout << "Invalid input, please pick a number..." << std::endl;
                    break;
                }
            }
        }
    return 0;
}



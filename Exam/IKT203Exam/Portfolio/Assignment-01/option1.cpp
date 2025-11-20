// Option 1 (Standard): Console Text Editor.
// Implements the user-facing console loop for the text editor.
// Handles line editing, undo/redo logic, and print job queue operations.

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

// Undo the last text modification.
// Reverses INSERT/DELETE actions by applying the inverse operation.
// Moves reversed action into redoStack.
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

// Redo the last undone modification.
// Re-applies an action previously undone.
// Pushes the executed action back into undoStack.
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

// Main menu loop for the Console Text Editor.
// Provides editing operations, queueing print jobs,
// and demonstrating FIFO behavior through job processing.
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
                for (int i = 0; i < document.GetSize(); i++) {
                    std::cout << document.GetAtIndex(i) << std::endl;
                }
                std::cout << std::endl;
                break;
            }

                // Build a single print job containing the entire document.
                // Snapshot is stored as a single string and enqueued.
            case 4: {
                std::cout << "----------Add print job----------" << std::endl;

                if (document.GetSize() == 0) {
                    std::cout << "Document is empty - nothing added to print queue." << std::endl;
                    break;
                }

                std::string job;
                for (int i = 0; i < document.GetSize(); i++) {
                    job += document.GetAtIndex(i) + "\n";
                }
                printQueue.Enqueue(job);
                std::cout << "Print job added to queue." << std::endl;
                break;
            }

                // Dequeue and print the next print job.
                // Demonstrates FIFO (First-In-First-Out) queue behavior.
            case 5: {
                if (printQueue.IsEmpty()) {
                    std::cout << "No prints jobs in queue." << std::endl;
                    break;
                }

                std::string job = printQueue.Dequeue();
                std::cout << "----------Printing job-----------" << std::endl;
                std::cout << job << std::endl;
                std::cout << "------------------------------------\n\n";
                break;

            }


                case 6: {
                    std::cout << "----------UNDO----------" <<std::endl;
                    Undo();
                    break;
                }

                case 7: {
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



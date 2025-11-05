#ifndef UTILS_H
#define UTILS_H
#include "TDoublyLinkedList.h"
#include "TStack.h"


class Utils {
    public:
    static int Choice();
    static int Insert(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index);
    static void PrintList(const TDoublyLinkedList &document);
    static int RemoveLine(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index);
    static int RandomInt(int, int);










};


#endif //PART1_UTILS_H
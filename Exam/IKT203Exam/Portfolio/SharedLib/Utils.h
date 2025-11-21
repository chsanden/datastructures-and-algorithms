#ifndef UTILS_H
#define UTILS_H
#include "TDoublyLinkedList.h"
#include "TPerson.h"
#include "TStack.h"

struct TPerson;

class Utils {
    public:
    static int Choice();
    static int Insert(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index);
    static void PrintList(const TDoublyLinkedList &document);
    static int RemoveLine(TDoublyLinkedList &document, TStack &undoStack, TStack &redoStack, int index);
    static int RandomInt(int, int);
    static int Partition(TPerson** arr, int startIndex, int endIndex);
    static void QuickSort(TPerson**, int, int);
    static bool CompareLastnames(const TPerson*, const TPerson*);
    static int BinarySearch(TPerson**, int, int, const std::string&);
    static int CountMatches(TPerson**, int, const std::string&);
};


#endif //PART1_UTILS_H
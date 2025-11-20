#ifndef TDOUBLYLINKEDLIST_H
#define TDOUBLYLINKEDLIST_H
#include <string>
#include <utility>


// Doubly linked list used to store document lines.
// Supports insertion, removal, and indexed access.
// Chosen because it allows efficient updates in the middle of the document.
class TDoublyLinkedList {

private:
    // Internal node storing a single line of text
    // and links to previous and next nodes.
    struct Node {
        std::string line;
        Node* next;
        Node* prev;
        explicit Node(std::string  text) : line(std::move(text)), next(nullptr), prev(nullptr) {}

        void SetNext(Node* node)
        {
            this->next = node;
        }
        void SetPrev(Node* node)
        {
            this->prev = node;
        }
        [[nodiscard]] Node* GetPrev() const
        {
            return this->prev;
        }
        [[nodiscard]] Node* GetNext() const
        {
            return this->next;
        }
        [[nodiscard]] std::string GetLine() const
        {
            return line;
        }

    };

    Node* head;
    Node* tail;
    int size;


public:
    TDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~TDoublyLinkedList();

    void Append(const std::string &line);
    void Prepend(const std::string& line);

    // Returns pointer to node at given index.
    // Linear traversal; used internally by Remove and InsertAtIndex.
    [[nodiscard]] Node* NavigateToNode(int index) const;

    // Removes a node at the given index.
    // Updates links and frees the removed node.
    void Remove(int index);

    // Returns the text stored at the given index.
    // Uses NavigateToNode internally.
    [[nodiscard]] std::string GetAtIndex(int index) const;
    void InsertAtIndex(int index, const std::string &line);
    [[nodiscard]] int GetSize() const;
};


#endif //TDOUBLYLINKEDLIST_H
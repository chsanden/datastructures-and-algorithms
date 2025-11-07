#ifndef IKT203_COURSE_ASSIGNMENTS_TBST_H
#define IKT203_COURSE_ASSIGNMENTS_TBST_H
#include "TEmployee.h"


struct Node {
    int key;
    TEmployee* data;
    Node* left;
    Node* right;
};


class TBST {
    private:
    Node* root;

    static Node* insert(Node* node, int key, TEmployee* data);

    static Node* search(Node* node, int key);

    static Node* remove(Node* node, int key);

    static void inorder(const Node* node);

    static void preorder(const Node* node);

    static void postorder(const Node* node);

    static void levelorder(const Node* node);

    static void destroy(Node* node);

    static Node* findMin(Node* node);

    public:
    TBST() = default;
    ~TBST() {destroy(root);}

    void Insert(int key, TEmployee* data);
    [[nodiscard]] TEmployee* Search(int key) const;
    void Delete(int key);

    void Inorder() const;
    void Preorder() const;
    void Postorder() const;

    void LevelOrder() const;
};


#endif //IKT203_COURSE_ASSIGNMENTS_TBST_H
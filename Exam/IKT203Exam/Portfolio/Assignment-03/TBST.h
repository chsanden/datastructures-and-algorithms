#ifndef IKT203_COURSE_ASSIGNMENTS_TBST_H
#define IKT203_COURSE_ASSIGNMENTS_TBST_H
#include "TEmployee.h"

struct BSTNode {
    int key;
    TEmployee* data;
    BSTNode* left;
    BSTNode* right;
};

class TBST {
    private:
    BSTNode* root;

    static BSTNode* insert(BSTNode* node, int key, TEmployee* data);
    static BSTNode* search(BSTNode* node, int key);
    static BSTNode* remove(BSTNode* node, int key);
    static void inorder(const BSTNode* node);
    static void preorder(const BSTNode* node);
    static void postorder(const BSTNode* node);
    static void levelorder(const BSTNode* node);
    static void destroy(BSTNode* node);
    static BSTNode* findMin(BSTNode* node);

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
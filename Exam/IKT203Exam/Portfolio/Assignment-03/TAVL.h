#ifndef IKT203_COURSE_ASSIGNMENTS_TAVL_H
#define IKT203_COURSE_ASSIGNMENTS_TAVL_H
#include <unordered_set>


struct AVLNode {
        int key;
        AVLNode* left;
        AVLNode* right;
        int height;

    explicit AVLNode(const int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

typedef bool (*FOrderTraversal)(const AVLNode* AVLNode);

class TAVL {
private:
    AVLNode* root;

    static int getHeight(const AVLNode* node);
    static int getBalance(const AVLNode *node);
    static AVLNode* rotateRight(AVLNode* y);
    static AVLNode* rotateLeft(AVLNode* x);
    static AVLNode* insert(AVLNode* n, int key);
    static void inorder(const AVLNode* node);
    static void preorder(const AVLNode* node);
    static void postorder(const AVLNode* node);
    static void levelorder(const AVLNode* node);



public:
    TAVL() : root(nullptr) {};
    ~TAVL() = default;

    void Insert(int key);
    static bool Inorder(const AVLNode* node);
    static bool Postorder(const AVLNode *node);
    static bool Preorder(const AVLNode *node);
    static bool LevelOrder(const AVLNode *node);
    void PrintOrder(FOrderTraversal);
    static void Populate(TAVL* AVLtree, int count, int minRange, int maxRange);


};


#endif //IKT203_COURSE_ASSIGNMENTS_TAVL_H
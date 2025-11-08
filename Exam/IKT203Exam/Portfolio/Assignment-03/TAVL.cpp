#include "TAVL.h"

#include <ios>
#include <iostream>
#include <unordered_set>
#include <bits/ios_base.h>

#include "TTreeQueue.h"
#include "Utils.h"

// Private helpers
int TAVL::getHeight(const AVLNode *node)
{
    return node ? node->height : 0;
}


int TAVL::getBalance(const AVLNode *node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode *TAVL::rotateRight(AVLNode *y)
{
    if (!y || !y->left)
        return y;

    AVLNode* x = y->left;
    AVLNode* n2 = x ? x->right : nullptr;

    x->right = y;
    y->left = n2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));


    return x;
}

AVLNode *TAVL::rotateLeft(AVLNode *x)
{
    if (!x || !x->right)
        return x;

    AVLNode* y = x->right;
    AVLNode* n2 = y ? y->left : nullptr;

    y->left = x;
    x->right = n2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Comment out std::cout lines for no rotation output lines
AVLNode *TAVL::insert(AVLNode *n, const int key)
{
    if (!n)
        return new AVLNode(key);
    if (key < n->key)
        n->left = insert(n->left, key);
    else if (key > n->key)
        n->right = insert(n->right, key);
    else
        return n;       // Ignore duplicates

    n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    const int balance = getBalance(n);

    if (balance > 1 && key < n->left->key)
    {
        std::cout << "L-L rotation on [" << n->key << "]" << std::endl;
        return rotateRight(n);
    }

    if (balance < -1 && key > n->right->key)
    {
        std::cout << "R-R rotation on [" << n->key << "]" << std::endl;
        return rotateLeft(n);
    }

    if (balance > 1 && key > n->left->key)
    {   std::cout << "L-R rotation on [" << n->key << "]" << std::endl;
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (balance < -1 && key < n->right->key)
    {   std::cout << "R-L rotation on [" << n->key << "]" << std::endl;
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

void TAVL::preorder(const AVLNode* node)
{
    if (!node)
        return;
    std::cout << "[" << node->key << "] ";
    preorder(node->left);
    preorder(node->right);
}

void TAVL::inorder(const AVLNode* node)
{
    if (!node)
        return;
    inorder(node->left);
    std::cout << "[" <<  node->key << "] ";
    inorder(node->right);
}

void TAVL::postorder(const AVLNode *node)
{
    if (!node)
        return;
    postorder(node->left);
    postorder(node->right);
    std::cout << "[" << node->key << "] ";
}

void TAVL::levelorder(const AVLNode* node)
{
    if (!node)
        return;

    TTreeQueue<AVLNode> q;
    q.Enqueue(const_cast<AVLNode*>(node));

    while (!q.IsEmpty()) {
        const AVLNode* cur = q.Dequeue();
        std::cout << "[" << cur->key << "] ";
        if (cur->left)
            q.Enqueue(cur->left);
        if (cur->right)
            q.Enqueue(cur->right);
    }

}

// Public functions
void TAVL::Insert(const int key)
{
    root = insert(root, key);
}

bool TAVL::Inorder(const AVLNode *node)
{
    if (!node)
        return true;
    inorder(node);
    std::cout << std::endl;
    return true;
}

bool TAVL::Postorder(const AVLNode *node)
{
    if (!node)
        return true;
    postorder(node);
    std::cout << std::endl;
    return true;
}

bool TAVL::Preorder(const AVLNode *node)
{
    if (!node)
        return true;
    preorder(node);
    std::cout << std::endl;
    return true;
}

bool TAVL::LevelOrder(const AVLNode *node)
{
    if (!node)
        return true;
    levelorder(node);
    std::cout << std::endl;
    return true;
}

void TAVL::PrintOrder(FOrderTraversal cb)
{
    if (!cb)
        return;
    cb(root);
}

///<summary> Populates AVL tree </summary
///<param name="avl"> The AVL tree to be populated</param>
///<param name"count">How many elements to be populated into the tree</param>
///<param name"minRange">Lower bounds of key value range (e.g., the lower limit of element value)</param>
///<param name"maxRange">Upper bounds of key value range (e.g., higher limit og element value)</param>
/// <returns>None</returns>
void TAVL::Populate(TAVL* avl, const int count, const int minRange, const int maxRange)
{
    std::unordered_set<int> AVLset;
    for (int i = 0; i < count; i++) {
        int val = Utils::RandomInt(minRange, maxRange);
        while (AVLset.count(val))
            val = Utils::RandomInt(minRange, maxRange);
        std::cout << "Inserting [" << val << "]" << std::endl;
        avl->Insert(val);
        AVLset.insert(val);
    }
}











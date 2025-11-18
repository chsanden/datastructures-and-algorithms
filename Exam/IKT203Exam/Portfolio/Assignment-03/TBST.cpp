#include "TBST.h"
#include <iostream>
#include "TTreeQueue.h"


void TBST::destroy(BSTNode *node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    // TBST owns the TEmployee* stored in each node, so delete it here.
    delete node->data;
    delete node;
}

///<summary> Insert node </summary
///<param name="key"> Node key value (int) </param>
///<param name="data"> Employee data (TEmployee) </param>
/// <returns> None </returns>
void TBST::Insert(const int key, TEmployee *data)
{
    root = insert(root, key, data);
}

BSTNode* TBST::insert(BSTNode* node, const int key, TEmployee *data)
{
    if (node == nullptr) {
        auto* n = new BSTNode{key, data, nullptr, nullptr};
        return n;
    }
    if (key < node->key)
        node->left = insert(node->left, key, data);
    else if (key > node->key)
        node->right = insert(node->right, key, data);
    else {
        // Duplicate key: do not modify the existing node.
        // 'data' was allocated by the caller, so we must delete it here
        // to avoid a memory leak.
        std::cout << "Duplicate key [" << key << "], ignoring insert." << std::endl;
        delete data;
    }
    return node;
}

///<summary> Search for node </summary
///<param name="key"> Node key value (int) </param>
/// <returns> TEmployee </returns>
TEmployee *TBST::Search(int key) const
{
    const BSTNode* result = search(root, key);
    return result ? result->data : nullptr;
}

BSTNode* TBST::search(BSTNode* node, const int key)
{
    if (node == nullptr)
        return nullptr;
    if (key == node->key)
        return node;
    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

///<summary> Delete node </summary
///<param name="key"> Node key value (int) </param>
/// <returns> None </returns>
void TBST::Delete(const int key)
{
    root = remove(root, key);
}

BSTNode *TBST::remove(BSTNode *node, const int key)
{
    if (node == nullptr)
        return nullptr;
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        // No children
        if (node->left == nullptr && node->right == nullptr) {
            delete node->data;
            delete node;
            return nullptr;
        }
        // Right child only
        if (node->left == nullptr) {
            BSTNode* child = node->right;
            delete node->data;
            delete node;
            return child;
        }
        // Left child only
        if (node->right == nullptr) {
            BSTNode* child = node->left;
            delete node->data;
            delete node;
            return child;
        }
        // Two children:
        // 1) Find the smallest node in the right subtree (inorder successor)
        // 2) Copy its key + data into the current node
        // 3) Remove the successor node from the right subtree
        else {
            BSTNode* minRight = findMin(node->right);
            node->key = minRight->key;
            node->data = minRight->data;
            node->right = remove(minRight->right, minRight->key);
        }
    }
    return node;
}

BSTNode* TBST::findMin(BSTNode* node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

// Traversals
// Private helpers
void TBST::preorder(const BSTNode* node)
{
    if (!node)
        return;
    std::cout << "[" << node->key << "] ";
    preorder(node->left);
    preorder(node->right);
}

void TBST::inorder(const BSTNode* node)
{
    if (!node)
        return;
    inorder(node->left);
    std::cout << "[" << node->key << "] ";
    inorder(node->right);
}

void TBST::postorder(const BSTNode *node)
{
    if (!node)
        return;
    postorder(node->left);
    postorder(node->right);
    std::cout << "[" << node->key << "] ";
}

void TBST::levelorder(const BSTNode* node)
{
    if (!node)
        return;

    TTreeQueue<BSTNode> q;
    q.Enqueue(const_cast<BSTNode*>(node));

    while (!q.IsEmpty()) {
        const BSTNode* cur = q.Dequeue();
        std::cout << "[" << cur->key << "] ";
        if (cur->left)
            q.Enqueue(cur->left);
        if (cur->right)
            q.Enqueue(cur->right);
    }
}

///<summary> Inorder sorting </summary
/// <returns> None </returns>
void TBST::Inorder() const
{
    inorder(root);
    std::cout << std::endl;
}

///<summary> Preorder sorting </summary
/// <returns> None </returns>
void TBST::Preorder() const
{
    preorder(root);
    std::cout << std::endl;
}

///<summary> Postorder sorting </summary
/// <returns> None </returns>
void TBST::Postorder() const
{
    postorder(root);
    std::cout << std::endl;
}

///<summary> LevelOrder sorting </summary
/// <returns> None </returns>
void TBST::LevelOrder() const
{
    levelorder(root);
    std::cout << std::endl;
}
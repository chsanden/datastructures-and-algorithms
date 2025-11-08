#include "TBST.h"

#include <iostream>

#include "TTreeQueue.h"


void TBST::destroy(BSTNode *node)
{
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node->data;
    delete node;
}

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
    else
        std::cout << "Error with node insertion" << std::endl;

    return node;
}

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
        // Two children
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

/// Traversals
/// Private helpers
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

void TBST::Inorder() const
{
    inorder(root);
    std::cout << std::endl;
}

void TBST::Preorder() const
{
    preorder(root);
    std::cout << std::endl;
}

void TBST::Postorder() const
{
    postorder(root);
    std::cout << std::endl;
}

void TBST::LevelOrder() const
{
    levelorder(root);
    std::cout << std::endl;
}
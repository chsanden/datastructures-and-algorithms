#include "TBST.h"

#include <iostream>

#include "TTreeQueue.h"


void TBST::destroy(Node *node)
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

Node* TBST::insert(Node* node, const int key, TEmployee *data)
{
    if (node == nullptr) {
        auto* n = new Node{key, data, nullptr, nullptr};
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
    const Node* result = search(root, key);
    return result ? result->data : nullptr;
}

Node* TBST::search(Node* node, const int key)
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

Node *TBST::remove(Node *node, const int key)
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
            Node* child = node->right;
            delete node->data;
            delete node;
            return child;
        }
        // Left child only
        if (node->right == nullptr) {
            Node* child = node->left;
            delete node->data;
            delete node;
            return child;
        }
        // Two children
        else {
            Node* minRight = findMin(node->right);
            node->key = minRight->key;
            node->data = minRight->data;
            node->right = remove(minRight->right, minRight->key);
        }
    }
    return node;
}

Node* TBST::findMin(Node* node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

/// Traversals
/// Private helpers
void TBST::preorder(const Node* node)
{
    if (!node)
        return;
    std::cout << "[" << node->key << "] ";
    preorder(node->left);
    preorder(node->right);
}

void TBST::inorder(const Node* node)
{
    if (!node)
        return;
    inorder(node->left);
    std::cout << "[" << node->key << "] ";
    inorder(node->right);
}

void TBST::postorder(const Node *node)
{
    if (!node)
        return;
    postorder(node->left);
    postorder(node->right);
    std::cout << "[" << node->key << "] ";
}

void TBST::levelorder(const Node* node)
{
    if (!node)
        return;

    TTreeQueue q;
    q.Enqueue(const_cast<Node*>(node));

    while (!q.IsEmpty()) {
        const Node* cur = q.Dequeue();
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




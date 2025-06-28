#ifndef AVLTree_H_
#define AVLTree_H_

#include <memory>
#include <iostream>
#include "pirate.h"
#include "consts.h"

using namespace std;

template <typename T>
class AVLTreeNode
{
public:
    shared_ptr<T> inner_node;
    int height;
    shared_ptr<AVLTreeNode<T>> left_son;
    shared_ptr<AVLTreeNode<T>> right_son;
    weak_ptr<AVLTreeNode<T>> parent;
    weak_ptr<AVLTreeNode<T>> max_Id;

    AVLTreeNode(const shared_ptr<T> &node)
        : inner_node(node), height(MINUS_ONE), left_son(nullptr), right_son(nullptr)
    {
        parent.reset();
    }

    ~AVLTreeNode() = default;

    void updateHeight()
    {
        int left_height = (left_son != nullptr) ? left_son->height : MINUS_ONE;
        int right_height = (right_son != nullptr) ? right_son->height : MINUS_ONE;
        height = (left_height < right_height) ? right_height + ONE : left_height + ONE;
    }

    int getBF() const
    {
        int left_height = (left_son != nullptr) ? left_son->height : MINUS_ONE;
        int right_height = (right_son != nullptr) ? right_son->height : MINUS_ONE;
        return left_height - right_height;
    }
};

template <typename T, class Compare>
class AVLTree
{
public:
    shared_ptr<AVLTreeNode<T>> root;
    Compare comp; // true if first argument is greater than second

    AVLTree(Compare comp) : root(nullptr), comp(comp){};

    ~AVLTree() = default;

    shared_ptr<AVLTreeNode<T>> find(shared_ptr<T> node);

    bool insert(const shared_ptr<T> &inner_node);

    bool remove(const shared_ptr<T> &inner_node);

private:
    shared_ptr<AVLTreeNode<T>> LL(shared_ptr<AVLTreeNode<T>> B);
    shared_ptr<AVLTreeNode<T>> RR(shared_ptr<AVLTreeNode<T>> A);
    shared_ptr<AVLTreeNode<T>> LR(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> RL(shared_ptr<AVLTreeNode<T>> node);
    shared_ptr<AVLTreeNode<T>> Rotate(shared_ptr<AVLTreeNode<T>> node);

    shared_ptr<AVLTreeNode<T>> nextNode(shared_ptr<AVLTreeNode<T>> node)
    {
        auto Next = node->right_son;
        while (Next->left_son != nullptr)
        {
            Next = Next->left_son;
        }
        return Next;
    }

    void updateMaxId(shared_ptr<AVLTreeNode<T>> node)
    {
        shared_ptr<AVLTreeNode<T>> left_max = (node->left_son != nullptr) ? node->left_son->max_Id.lock() : nullptr;
        shared_ptr<AVLTreeNode<T>> right_max = (node->right_son != nullptr) ? node->right_son->max_Id.lock() : nullptr;
        shared_ptr<AVLTreeNode<T>> max = node;
        if (left_max != nullptr && comp(max->inner_node, left_max->inner_node))
            max = left_max;
        if (right_max != nullptr && comp(max->inner_node, right_max->inner_node))
            max = right_max;
        node->max_Id = max;
    }
    void updateData(shared_ptr<AVLTreeNode<T>> node)
    {
        node->updateHeight();
        updateMaxId(node);
    }

    shared_ptr<AVLTreeNode<T>> removeOnlyChild(shared_ptr<AVLTreeNode<T>> node);
};

template <typename T, class Compare>
bool AVLTree<T, Compare>::insert(const shared_ptr<T> &inner_node)
{
    auto node = make_shared<AVLTreeNode<T>>(inner_node);
    updateData(node);
    if (root == nullptr)
    {
        root = node;
        return true;
    }

    auto parent = find(inner_node);
    if (parent->inner_node == inner_node)
        return false;
    if (comp(parent->inner_node, inner_node))
    {
        parent->right_son = node;
    }
    else
    {
        parent->left_son = node;
    }
    node->parent = parent;

    while (parent != nullptr)
    {
        updateData(parent);
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
        }
        node = parent;
        parent = parent->parent.lock();
    }
    root = node;
    return true;
}

template <typename T, class Compare>
bool AVLTree<T, Compare>::remove(const shared_ptr<T> &inner_node)
{
    if (root == nullptr)
    {
        return false;
    }

    auto node = find(inner_node);

    if (node->inner_node != inner_node)
        return false;

    auto parent = node->parent.lock();
    if (node->left_son == nullptr || node->right_son == nullptr)
    {
        node = removeOnlyChild(node);
    }
    else
    {
        auto next = nextNode(node);
        node->inner_node = next->inner_node;
        node = next;
        parent = node->parent.lock();
        node = removeOnlyChild(node);
    }

    while (parent != nullptr)
    {
        updateData(parent);
        if (parent->getBF() == POSITIVE_UNBALANCED || parent->getBF() == NEGATIVE_UNBALANCED)
        {
            parent = Rotate(parent);
        }
        node = parent;
        parent = parent->parent.lock();
    }
    root = node;
    return true;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::find(shared_ptr<T> node)
{
    shared_ptr<AVLTreeNode<T>> current = root;
    shared_ptr<AVLTreeNode<T>> previous = current;
    while (current != nullptr)
    {
        previous = current;
        if (comp(node, current->inner_node))
            current = current->left_son;
        else if (comp(current->inner_node, node))
            current = current->right_son;
        else
            return current;
    }
    return previous;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::LL(shared_ptr<AVLTreeNode<T>> B)
{
    auto A = B->left_son;
    auto AR = A->right_son;
    auto parent = B->parent.lock();

    B->left_son = nullptr;
    A->right_son = B;

    B->left_son = AR;

    A->parent = parent;
    B->parent = A;
    if (AR)
        AR->parent = B;
    if (parent)
    {
        if (parent->left_son == B)
            parent->left_son = A;
        else
            parent->right_son = A;
        updateData(parent);
    }

    updateData(B);
    updateData(A);

    return A;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::RR(shared_ptr<AVLTreeNode<T>> A)
{
    auto B = A->right_son;
    auto BL = B->left_son;
    auto parent = A->parent.lock();

    A->right_son = nullptr;
    B->left_son = A;

    A->right_son = BL;

    B->parent = parent;
    A->parent = B;
    if (BL)
        BL->parent = A;
    if (parent)
    {
        if (parent->left_son == A)
            parent->left_son = B;
        else
            parent->right_son = B;
        updateData(parent);
    }

    updateData(A);
    updateData(B);

    return B;
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::LR(shared_ptr<AVLTreeNode<T>> node)
{
    node->left_son = RR(node->left_son);
    return LL(node);
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::RL(shared_ptr<AVLTreeNode<T>> node)
{
    node->right_son = LL(node->right_son);
    return RR(node);
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::Rotate(shared_ptr<AVLTreeNode<T>> node)
{
    if (node->getBF() == 2)
    {
        if (node->left_son->getBF() >= ZERO)
            return LL(node);
        else
            return LR(node);
    }
    else
    {
        if (node->right_son->getBF() <= ZERO)
            return RR(node);
        else
            return RL(node);
    }
}

template <typename T, class Compare>
shared_ptr<AVLTreeNode<T>> AVLTree<T, Compare>::removeOnlyChild(shared_ptr<AVLTreeNode<T>> node)
{
    shared_ptr<AVLTreeNode<T>> temp;
    if (node->left_son == nullptr && node->right_son == nullptr)
    {
        temp = nullptr;
    }
    else if (node->left_son == nullptr)
    {
        temp = node->right_son;
    }
    else
    {
        temp = node->left_son;
    }

    if (node->parent.lock() == nullptr)
    {
        root = temp;
        if (temp != nullptr)
            temp->parent.reset();
    }
    else
    {
        if (node->parent.lock()->left_son == node)
        {
            node->parent.lock()->left_son = temp;
        }
        else
        {
            node->parent.lock()->right_son = temp;
        }

        if (temp != nullptr)
            temp->parent = node->parent.lock();
    }

    node->parent.reset();
    node->left_son = nullptr;
    node->right_son = nullptr;
    return temp;
}

#endif // AVLTree_H_
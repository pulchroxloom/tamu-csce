#ifndef _BST_TPP_
#define _BST_TPP_

#include "bst.hpp"

template <typename T>
std::string BST<T>::print_separator = "    ";

template <typename T>
void BST<T>::copy(Node *their)
{
    if (their)
    {
        insert(their->obj);
        copy(their->left);
        copy(their->right);
    }
}

template <typename T>
void BST<T>::destroy(Node *n)
{
    if (n)
    {
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

template <typename T>
void BST<T>::reset()
{
    len = 0;
    root = nullptr;
}

template <typename T>
void BST<T>::print(std::ostream &os, const Node *n, size_t depth) const
{
    if (n)
    {
        print(os, n->right, depth + 1);
        for (size_t i = 0; i < depth; ++i)
            os << print_separator;
        os << n->obj << '\n';
        print(os, n->left, depth + 1);
    }
}

template <typename T>
BST<T>::Node::Node(T object, Node *leftChild, Node *rightChild) : obj{object}, left{leftChild}, right{rightChild} {}

template <typename T>
BST<T>::BST() : len{0}, root{nullptr} {}

template <typename T>
BST<T>::BST(const BST<T> &bst) : len{0}, root{nullptr}
{
    copy(bst.root);
}

template <typename T>
BST<T>::BST(BST<T> &&bst) : len{bst.len}, root{bst.root}
{
    bst.reset();
}

template <typename T>
BST<T>::~BST()
{
    clear();
}

template <typename T>
BST<T> &BST<T>::operator=(const BST<T> &bst)
{
    if (this != &bst)
    {
        clear();
        copy(bst.root);
    }
    return *this;
}

template <typename T>
BST<T> &BST<T>::operator=(BST<T> &&bst)
{
    if (this != &bst)
    {
        clear();
        len = bst.len;
        root = bst.root;
        bst.reset();
    }
    return *this;
}

template <typename T>
bool BST<T>::empty() const
{
    return size() == 0;
}

template <typename T>
size_t BST<T>::size() const
{
    return len;
}

template <typename T>
size_t BST<T>::length() const
{
    return size();
}

template <typename T>
const typename BST<T>::Node *BST<T>::search(const T &data) const
{
    const Node *curr = root;
    while (curr && curr->obj != data)
    {
        if (curr->obj < data)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    return curr;
}

template <typename T>
typename BST<T>::Node *BST<T>::search(const T &data)
{
    Node *curr = root;
    while (curr && curr->obj != data)
    {
        if (curr->obj < data)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    return curr;
}

template <typename T>
typename BST<T>::Node &BST<T>::insert(const T &data)
{
    Node *curr = root;
    while (curr)
    {
        if (curr->obj < data)
        {
            if (curr->right)
            {
                curr = curr->right;
            }
            else
            {
                curr->right = new Node(data);
                ++len;
                return *curr->right;
            }
        }
        else
        {
            if (curr->left)
            {
                curr = curr->left;
            }
            else
            {
                curr->left = new Node(data);
                ++len;
                return *curr->left;
            }
        }
    }
    root = new Node(data);
    ++len;
    return *root;
}



template <typename T>
void BST<T>::clear()
{
    destroy(root);
    reset();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BST<T> &bst)
{
    bst.print(os, bst.root);
    return os;
}

#endif
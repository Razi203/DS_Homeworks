#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include "consts.h"
using std::shared_ptr;

template <typename T>
class HashNode
{
public:
    HashNode(int key) : id(key)
    {
        value = shared_ptr<T>(key);
        next = nullptr;
    }

    shared_ptr<T> getValue() const
    {
        return value;
    }

    int getId() const
    {
        return id;
    }

    shared_ptr<HashNode<T>> getNext() const
    {
        return next;
    }

    void setNext(shared_ptr<HashNode<T>> node)
    {
        next = node;
    }

private:
    int id;
    shared_ptr<T> value;
    shared_ptr<HashNode<T>> next;
};

template <typename T>
class HashTable
{
public:
    HashTable();

    ~HashTable();

    shared_ptr<T> &insert(int key);

    shared_ptr<T> &get(int key) const;

    int getSize() const;

    void sizeUp();

    bool tooBig() const;

private:
    int hash(int key);

    int table_size;
    int size;
    shared_ptr<HashNode<T>> *table;
};

template <typename T>
HashTable<T>::HashTable() : table_size(INITIAL_TABLE_SIZE), size(ZERO)
{
    table = new shared_prt<HashNode<T>>[table_size];
    for (int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

template <typename T>
HashTable<T>::~HashTable()
{
    delete[] table;
}

template <typename T>
int HashTable<T>::hash(int key)
{
    return key % table_size;
}

template <typename T>
int HashTable<T>::getSize() const
{
    return size;
}

template <typename T>
shared_ptr<T> &HashTable<T>::get(int key) const
{
    int index = hash(key);
    shared_ptr<HashNode<T>> node = table[index];
    if (node == nullptr)
    {
        return nullptr;
    }
    while (node != nullptr && node->getId() != key)
    {
        node = node->getNext();
    }
    return node == nullptr ? nullptr : node->getValue();
}

template <typename T>
bool HashTable<T>::tooBig() const
{
    return size >= table_size * LOAD_FACTOR;
}

template <typename T>
shared_ptr<T> &HashTable<T>::insert(int key)
{
    int index = hash(key);
    shared_ptr<HashNode<T>> node = table[index];
    if (node == nullptr)
    {
        auto node = shared_ptr<HashNode<T>>(key);
        table[index] = node;
        size++;
        if (tooBig())
        {
            sizeUp();
        }
        return node->getValue();
    }

    while (node->getNext() != nullptr && node->getId() != key)
    {
        node = node->getNext();
    }

    if (node->getId() == key)
    {
        return nullptr;
    }

    auto newNode = shared_ptr<HashNode<T>>(key);
    node->setNext(newNode);
    size++;
    if (tooBig())
    {
        sizeUp();
    }
    return newNode->getValue();
}

template <typename T>
void HashTable<T>::sizeUp()
{
    int old_size = table_size;
    table_size *= SIZING_FACTOR;

    shared_ptr<HashNode<T>> *old_table = table;
    table = new shared_ptr<HashNode<T>>[table_size];

    for (int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }

    for (int i = 0; i < old_size; i++)
    {
        shared_ptr<HashNode<T>> node = old_table[i];
        while (node != nullptr)
        {
            shared_ptr<HashNode<T>> next = node->getNext();
            int index = hash(node->getId());
            node->setNext(table[index]);
            table[index] = node;
            node = next;
        }
    }

    delete[] old_table;
}
#endif // HASHTABLE_H
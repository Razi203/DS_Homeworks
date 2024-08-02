#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include "consts.h"
using std::shared_ptr;

/**
 * HashNode class
 * The class represents a node in the hash table with its data.
 * Class fields:
 * - id: the id of the pirate/fleet of the node.
 * - value: the pirate or fleet of the node.
 * - next: the next node in the linked list in the Hash Table.
 */
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

/**
 * HashTable class
 * The class is a generic hash table with dynamic size and no removing of elements.
 * Class fields:
 * - table_size: the maximum size of the table as of that moment.
 * - size: the current number of elements in the hash table.
 * - table: the dynamic array of the hash table.
 *
 * Class methods:
 * - insert - inserts a new element to the hash table using it's id.
 *            return value:
 *             - nullptr if the element is already in the hash table.
 *             - (otherwise if it was inserted) the element.
 * - get - returns the element in the hash table with the given id or nullptr if it doesn't exist.
 *
 */
template <typename T>
class HashTable
{
public:
    HashTable();

    ~HashTable();

    shared_ptr<T> &insert(int key);

    shared_ptr<T> &get(int key) const;

private:
    int hash(int key);
    void sizeUp();
    bool tooBig() const;
    void add_aux(shared_ptr<HashNode<T>> node);

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
        sizeUp;
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
    sizeUp();

    return newNode->getValue();
}

template <typename T>
void HashTable<T>::sizeUp()
{
    if (!tooBig())
    {
        return;
    }
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
            add_aux(node);
            node = next;
        }
    }

    delete[] old_table;
}

template <typename T>
void HashTable<T>::add_aux(shared_ptr<HashNode<T>> node)
{
    node->setNext(nullptr);
    int index = hash(node->getId());
    shared_ptr<HashNode<T>> current = table[index];
    if (current == nullptr)
    {
        table[index] = node;
    }
    else
    {
        while (current->getNext() != nullptr)
        {
            current = current->getNext();
        }
        current->setNext(node);
    }
}
#endif // HASHTABLE_H
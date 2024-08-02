#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include "consts.h"
using std::shared_ptr;

template <typename T>
class HashNode
{
public:
    HashNode(int key) : id(key) {}

    shared_ptr<T> getValue()
    {
        return value;
    }

    int getId()
    {
        return id;
    }

    shared_ptr<HashNode<T>> getNext()
    {
        return next;
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

    shared_ptr<HashNode<T>> &insert(int key);

    void remove(int key);

    Value get(int key);

    bool isEmpty();

    int getSize();

    void sizeUp();

private:
    int hash(int key);

    int table_size = INITIAL_TABLE_SIZE;
    int size = ZERO;
    shared_ptr<HashNode<T>> table[table_size];
};

template <typename T>
HashTable<T>::HashTable()
{
    for (int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

#endif // HASHTABLE_H
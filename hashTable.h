#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
using std::shared_ptr;

template <typename T>
class HashTable
{
public:
    HashTable();

    ~HashTable();

    shared_ptr<T> &insert(int key);

    void remove(int key);

    Value get(int key);

    bool isEmpty();

    int getSize();

    void sizeUp();

private:
    int hash(int key);

    int table_size = 100;
    int size = 0;
    shared_ptr<T> table[table_size];
};

#endif // HASHTABLE_H
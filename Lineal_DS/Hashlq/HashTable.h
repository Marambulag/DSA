#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

enum class CollisionResolutionMethod {
    LINEAR_PROBING,
    QUADRATIC_PROBING
};

class HashTable {
private:
    int size;
    std::vector<int> table;
    int numElements;
    CollisionResolutionMethod collisionResolutionMethod;

    int hashFunction(int key) const;
    int linearProbing(int hash, int i) const;
    int quadraticProbing(int hash, int i) const;
    void rehash();

public:
    HashTable(int tableSize, CollisionResolutionMethod method);

    void insert(int key);
    bool search(int key) const;
    void remove(int key);
    void display() const;
};

#endif // HASHTABLE_H

#include "HashTable.h"
#include <stdexcept>

HashTable::HashTable(int tableSize, CollisionResolutionMethod method)
    : size(tableSize), collisionResolutionMethod(method), numElements(0) {
    table.resize(size, -1); // Initialize the table with -1 indicating empty slots
}

int HashTable::hashFunction(int key) const {
    return key % size;
}

int HashTable::linearProbing(int hash, int i) const {
    return (hash + i) % size;
}

int HashTable::quadraticProbing(int hash, int i) const {
    return (hash + i * i) % size;
}

void HashTable::rehash() {
    int oldSize = size;
    size *= 2;
    numElements = 0;
    std::vector<int> oldTable = table;
    table.clear();
    table.resize(size, -1);

    for (int key : oldTable) {
        if (key != -1) {
            insert(key);
        }
    }
}

void HashTable::insert(int key) {
    if (numElements >= 0.7 * size) {
        rehash();
    }

    int hash = hashFunction(key);
    int i = 0;
    int index;
    do {
        if (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING) {
            index = linearProbing(hash, i);
        } else {
            index = quadraticProbing(hash, i);
        }
        if (table[index] == -1 || table[index] == -2) { // -2 indicates a previously occupied slot
            table[index] = key;
            numElements++;
            return;
        }
        i++;
    } while (i != size);

    throw std::overflow_error("HashTable is full, cannot insert key.");
}

bool HashTable::search(int key) const {
    int hash = hashFunction(key);
    int i = 0;
    int index;
    do {
        if (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING) {
            index = linearProbing(hash, i);
        } else {
            index = quadraticProbing(hash, i);
        }
        if (table[index] == key) {
            return true;
        }
        i++;
    } while (table[index] != -1 && i != size);
    return false;
}

void HashTable::remove(int key) {
    int hash = hashFunction(key);
    int i = 0;
    int index;
    do {
        if (collisionResolutionMethod == CollisionResolutionMethod::LINEAR_PROBING) {
            index = linearProbing(hash, i);
        } else {
            index = quadraticProbing(hash, i);
        }
        if (table[index] == key) {
            table[index] = -2; // Mark the slot as previously occupied
            numElements--;
            return;
        }
        i++;
    } while (table[index] != -1 && i != size);
}

void HashTable::display() const {
    for (int i = 0; i < size; ++i) {
        if (table[i] == -1) {
            std::cout << "Index " << i << ": nullptr\n";
        } else if (table[i] == -2) {
            std::cout << "Index " << i << ": (deleted)\n";
        } else {
            std::cout << "Index " << i << ": " << table[i] << "\n";
        }
    }
    std::cout << std::endl;
}

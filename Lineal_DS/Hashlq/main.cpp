#include "HashTable.h"

// Function prototype
void testHashTable(CollisionResolutionMethod method);

void testHashTable(CollisionResolutionMethod method) {
    // Hash table size
    int tableSize = 10;
    HashTable hashTable(tableSize, method);

    // Insert elements
    hashTable.insert(5);
    hashTable.insert(15);
    hashTable.insert(25);
    hashTable.insert(2);
    hashTable.insert(10);

    // Display the hash table
    std::cout << "Hash Table (" << (method == CollisionResolutionMethod::LINEAR_PROBING ? "Linear Probing" : "Quadratic Probing") << "):\n";
    hashTable.display();

    // Search elements
    std::cout << "\nSearching for 15: " << (hashTable.search(15) ? "Found" : "Not Found") << "\n";
    std::cout << "Searching for 9: " << (hashTable.search(9) ? "Found" : "Not Found") << "\n";

    // Remove an element
    hashTable.remove(15);
    std::cout << "\nAfter removing 15:\n";
    hashTable.display();
}

int main() {
    // Test with Linear Probing
    testHashTable(CollisionResolutionMethod::LINEAR_PROBING);

    // Test with Quadratic Probing
    testHashTable(CollisionResolutionMethod::QUADRATIC_PROBING);

    return 0;
}

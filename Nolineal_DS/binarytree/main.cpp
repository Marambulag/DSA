#include <iostream>
#include "BinaryTree.hpp"

int main() {
    BinaryTree tree;


    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 70);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 60);
    tree.root = tree.insert(tree.root, 80);

    std::cout << "Inorden: ";
    tree.inOrderTraversal(tree.root);
    std::cout << "\n";

    std::cout << "Preorden: ";
    tree.preOrderTraversal(tree.root);
    std::cout << "\n";

    std::cout << "Postorden: ";
    tree.postOrderTraversal(tree.root);
    std::cout << "\n";

  
    int valueToSearch = 40;
    Node* result = tree.search(tree.root, valueToSearch);
    if (result != nullptr) {
        std::cout << "Valor encontrado: " << result->data << "\n";
    } else {
        std::cout << "Valor no encontrado\n";
    }

    std::cout << "Eliminando 20...\n";
    tree.root = tree.remove(tree.root, 20);

    std::cout << "Inorden después de eliminar 20: ";
    tree.inOrderTraversal(tree.root);
    std::cout << "\n";

    return 0;
}

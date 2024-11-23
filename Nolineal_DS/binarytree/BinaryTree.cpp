#include "BinaryTree.hpp"
#include <iostream>

Node::Node(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

BinaryTree::BinaryTree() {
    root = nullptr;
}

Node* BinaryTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else {
        node->right = insert(node->right, value);
    }

    return node;
}

Node* BinaryTree::search(Node* node, int value) {
    if (node == nullptr || node->data == value) {
        return node;
    }

    if (value < node->data) {
        return search(node->left, value);
    }
    return search(node->right, value);
}

Node* BinaryTree::minValueNode(Node* node) {
    Node* current = node;

    // El nodo más a la izquierda es el mínimo
    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

Node* BinaryTree::remove(Node* node, int value) {
    if (node == nullptr) {
        return node;
    }

    // Buscar el nodo a eliminar
    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        // Caso 1: Nodo sin hijos o con un solo hijo
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Caso 2: Nodo con dos hijos
        Node* temp = minValueNode(node->right);  // Encuentra el sucesor
        node->data = temp->data;                 // Reemplaza el valor actual
        node->right = remove(node->right, temp->data); // Elimina el sucesor
    }

    return node;
}

void BinaryTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }
}

void BinaryTree::preOrderTraversal(Node* node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void BinaryTree::postOrderTraversal(Node* node) {
    if (node != nullptr) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

#include "Node.hpp"

Node::Node(Country value) {
    this->height = 0;
    this->name = value.getName();
    this->key = value;
    this->left = nullptr;
    this->right = nullptr;
}


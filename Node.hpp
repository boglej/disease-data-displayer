#pragma once
#include "Country.hpp"
#include <string>
struct Node {
    std::string name;
    Country key;
    int height;
    struct Node* left;
    struct Node* right;
    Node(Country value);
};

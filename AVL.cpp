#include <iostream>
#include "AVL.h"
#include "Node.hpp"

AVL::AVL() {
	root = nullptr;
	height = 0;
}

int AVL::maximum(int x, int y) {
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}

int AVL::GetHeight(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		return node->height;
	}
}

void AVL::SetRoot(Node* node) {
	this->root = node;
}

Node* AVL::GetRoot() {
	return root;
}

Node* AVL::RotateRight(Node* node) {
	if (node == nullptr) {
		return node;
	}
	Node* grandchild = node->left->right;
	Node* newRoot = node->left;
	newRoot->right = node;
	node->left = grandchild;

	//new heights
	node->height = maximum(GetHeight(node->left), GetHeight(node->right)) + 1;
	newRoot->height = maximum(GetHeight(newRoot->left), GetHeight(newRoot->right)) + 1;
	return newRoot;
}

Node* AVL::RotateLeft(Node* node) {
	if (node == nullptr) {
		return node;
	}
	Node* grandchild = node->right->left;
	Node* newRoot = node->right;
	newRoot->left = node;
	node->right = grandchild;

	//new heights
	node->height = maximum(GetHeight(node->left), GetHeight(node->right)) + 1;
	newRoot->height = maximum(GetHeight(newRoot->left), GetHeight(newRoot->right)) + 1;

	return newRoot;
}

int AVL::CheckBalance(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		int heightL = 0;
		int heightR = 0;
		if (node->left != nullptr) {
			heightL = node->left->height;
		}
		if (node->right != nullptr) {
			heightR = node->right->height;
		}
		int balanceFactor = heightL - heightR;
		return balanceFactor;
	}
}

void AVL::Preorder(Node* node) {
	if (node == nullptr) {
		return;
	}

	//puts data to memory for data
	std::cout << node->name << std::endl;

	Preorder(node->left);
	Preorder(node->right);
}

void AVL::Inorder(Node* node) {
	if (node == nullptr) {
		return;
	}

	Inorder(node->left);
	//puts data to memory for data
	std::cout << node->name << std::endl;

	Inorder(node->right);
}

Node* AVL::Insert(Node* node, Country country) {

	if (node == nullptr) {
		Node* temp = new Node(country);
		root = temp;
		return temp;
	}
	//ensures the data passes conditions

	//checks and recurses to find where it should go
	if (country.getName() < node->key.getName()) {
		node->left = Insert(node->left, country);
	}
	else if (country.getName() > node->key.getName()) {
		node->right = Insert(node->right, country);
	}
	else {
		std::string currentDate = country.getDate();
		node->key.insertDateData(country.getDate(), country.getNewCases(currentDate), country.getCumulativeCases(currentDate), country.getNewDeaths(currentDate), country.getCumulativeDeaths(currentDate));
		root = node;
		return node;
	}
	//increase heights;
	int heightL = 0;
	int heightR = 0;
	if (node->left != nullptr) {
		heightL = node->left->height;
	}
	if (node->right != nullptr) {
		heightR = node->right->height;
	}
	node->height = maximum(heightL, heightR) + 1;

	//get the balance factor
	int balanceCheck = CheckBalance(node);

	//rotations for the four cases
		//left left
	if (balanceCheck > 1 && country.getName() < node->left->key.getName()) {
		node = RotateRight(node);
		root = node;
		return node;
	}
	//left right
	if (balanceCheck > 1 && country.getName() > node->left->key.getName()) {
		node->left = RotateLeft(node->left);
		root = node;
		return RotateRight(node);
	}
	//right right
	if (balanceCheck < -1 && country.getName() > node->right->key.getName()) {
		node = RotateLeft(node);
		root = node;
		return node;
	}
	//right left
	if (balanceCheck < -1 && country.getName() < node->right->key.getName()) {
		node->right = RotateRight(node->right);
		node = RotateLeft(node);
		root = node;
		return node;
	}
	root = node;
	return node;
}

void AVL::AssignCountry(Node *node, std::string _countryName, Country &countryObj) {

    if(node == nullptr){
        return;
    }

    if(node->key.getName() == _countryName){
        countryObj = node->key; //assign country OBJ in main to this correct obbj
    }

    AssignCountry(node->left, _countryName, countryObj);
    AssignCountry(node->right, _countryName, countryObj);
}

//obtain a vector of all countries. Used in sorting
void AVL::LoadCountries(Node* node, std::vector<Country> &countryVec) {
    if (node == nullptr) {
        return;
    }

    LoadCountries(node->left, countryVec);
    //puts data to memory for data
    countryVec.push_back(node->key);

    LoadCountries(node->right, countryVec);
}
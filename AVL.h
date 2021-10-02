#pragma once
#include "Node.hpp"
#include "Country.hpp"

class AVL {
	Node* root;
	int height;
public:
	AVL();
	int maximum(int x, int y);
	int GetHeight(Node* node);
	void SetRoot(Node* node);
	void AssignCountry(Node* node, std::string _countryName, Country &countryObj);
	Node* GetRoot();
	Node* RotateRight(Node* node);
	Node* RotateLeft(Node* node);
	int CheckBalance(Node* node);
	void Preorder(Node* node);
	void Inorder(Node* node);
	Node* Insert(Node* node, Country country);

    void LoadCountries(Node *node, std::vector<Country> &countryVec);
};
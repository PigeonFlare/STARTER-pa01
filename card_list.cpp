// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h

#include "card_list.h"

using namespace std;

CardBST::Node::Node(const Card& card)
		: data(card), left(nullptr), right(nullptr), parent(nullptr) {}

CardBST::CardBST() : root(nullptr) {}

CardBST::~CardBST() {
	clear(root);
}

void CardBST::insert(const Card& card) {
	if (!root) {
		root = new Node(card);
		return;
	}

	Node* current = root;
	Node* parent = nullptr;

	while (current) {
		parent = current;
		if (card < current->data) {
			current = current->left;
		} else if (card > current->data) {
			current = current->right;
		} else {
			return;
		}
	}

	Node* node = new Node(card);
	node->parent = parent;
	if (card < parent->data) {
		parent->left = node;
	} else {
		parent->right = node;
	}
}

void CardBST::remove(const Card& card) {
	Node* target = findNode(card);
	if (!target) {
		return;
	}

	if (!target->left) {
		transplant(target, target->right);
		delete target;
		return;
	}

	if (!target->right) {
		transplant(target, target->left);
		delete target;
		return;
	}

	Node* successorNode = minimum(target->right);
	if (successorNode->parent != target) {
		transplant(successorNode, successorNode->right);
		successorNode->right = target->right;
		successorNode->right->parent = successorNode;
	}

	transplant(target, successorNode);
	successorNode->left = target->left;
	successorNode->left->parent = successorNode;
	delete target;
}

bool CardBST::contains(const Card& card) const {
	return findNode(card) != nullptr;
}

void CardBST::printInOrder(ostream& os) const {
	printInOrder(root, os);
}

bool CardBST::empty() const {
	return root == nullptr;
}

CardBST::Iterator CardBST::begin() const {
	return Iterator(this, minimum(root));
}

CardBST::Iterator CardBST::end() const {
	return Iterator(this, nullptr);
}

CardBST::Iterator CardBST::rbegin() const {
	return Iterator(this, maximum(root));
}

CardBST::Iterator CardBST::rend() const {
	return Iterator(this, nullptr);
}

CardBST::Node* CardBST::findNode(const Card& card) const {
	Node* current = root;
	while (current) {
		if (card < current->data) {
			current = current->left;
		} else if (card > current->data) {
			current = current->right;
		} else {
			return current;
		}
	}
	return nullptr;
}

CardBST::Node* CardBST::minimum(Node* node) const {
	if (!node) {
		return nullptr;
	}
	while (node->left) {
		node = node->left;
	}
	return node;
}

CardBST::Node* CardBST::maximum(Node* node) const {
	if (!node) {
		return nullptr;
	}
	while (node->right) {
		node = node->right;
	}
	return node;
}

CardBST::Node* CardBST::successor(Node* node) const {
	if (!node) {
		return nullptr;
	}
	if (node->right) {
		return minimum(node->right);
	}

	Node* parent = node->parent;
	while (parent && node == parent->right) {
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

CardBST::Node* CardBST::predecessor(Node* node) const {
	if (!node) {
		return nullptr;
	}
	if (node->left) {
		return maximum(node->left);
	}

	Node* parent = node->parent;
	while (parent && node == parent->left) {
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void CardBST::clear(Node* node) {
	if (!node) {
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}

void CardBST::printInOrder(Node* node, ostream& os) const {
	if (!node) {
		return;
	}
	printInOrder(node->left, os);
	os << node->data << endl;
	printInOrder(node->right, os);
}

void CardBST::transplant(Node* oldNode, Node* newNode) {
	if (!oldNode->parent) {
		root = newNode;
	} else if (oldNode == oldNode->parent->left) {
		oldNode->parent->left = newNode;
	} else {
		oldNode->parent->right = newNode;
	}

	if (newNode) {
		newNode->parent = oldNode->parent;
	}
}

CardBST::Iterator::Iterator() : tree(nullptr), current(nullptr) {}

CardBST::Iterator::Iterator(const CardBST* tree, Node* current)
		: tree(tree), current(current) {}

const Card& CardBST::Iterator::operator*() const {
	return current->data;
}

const Card* CardBST::Iterator::operator->() const {
	return &(current->data);
}

CardBST::Iterator& CardBST::Iterator::operator++() {
	if (!tree || !current) {
		return *this;
	}
	current = tree->successor(current);
	return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
	if (!tree || !current) {
		return *this;
	}
	current = tree->predecessor(current);
	return *this;
}

bool CardBST::Iterator::operator==(const Iterator& other) const {
	return tree == other.tree && current == other.current;
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

void playGame(CardBST& alice, CardBST& bob, ostream& os) {
	while (true) {
		bool aliceMatched = false;
		for (auto it = alice.begin(); it != alice.end();) {
			Card current = *it;
			++it;
			if (bob.contains(current)) {
				os << "Alice picked matching card " << current << endl;
				alice.remove(current);
				bob.remove(current);
				aliceMatched = true;
				break;
			}
		}

		if (!aliceMatched) {
			break;
		}

		bool bobMatched = false;
		for (auto it = bob.rbegin(); it != bob.rend();) {
			Card current = *it;
			--it;
			if (alice.contains(current)) {
				os << "Bob picked matching card " << current << endl;
				alice.remove(current);
				bob.remove(current);
				bobMatched = true;
				break;
			}
		}

		if (!bobMatched) {
			break;
		}
	}
}


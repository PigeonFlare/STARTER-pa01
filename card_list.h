// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"

class CardBST {
public:
	class Iterator;

	CardBST();
	CardBST(const CardBST& other) = delete;
	CardBST& operator=(const CardBST& other) = delete;
	~CardBST();

	void insert(const Card& card);
	void remove(const Card& card);
	bool contains(const Card& card) const;
	void printInOrder(std::ostream& os = std::cout) const;
	bool empty() const;

	Iterator begin() const;
	Iterator end() const;
	Iterator rbegin() const;
	Iterator rend() const;

private:
	struct Node {
		Card data;
		Node* left;
		Node* right;
		Node* parent;

		explicit Node(const Card& card);
	};

	Node* root;

	Node* findNode(const Card& card) const;
	Node* minimum(Node* node) const;
	Node* maximum(Node* node) const;
	Node* successor(Node* node) const;
	Node* predecessor(Node* node) const;
	void clear(Node* node);
	void printInOrder(Node* node, std::ostream& os) const;
	void transplant(Node* oldNode, Node* newNode);

public:
	class Iterator {
	public:
		Iterator();

		const Card& operator*() const;
		const Card* operator->() const;

		Iterator& operator++();
		Iterator& operator--();

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

	private:
		friend class CardBST;
		Iterator(const CardBST* tree, Node* current);

		const CardBST* tree;
		Node* current;
	};
};

void playGame(CardBST& alice, CardBST& bob, std::ostream& os = std::cout);

#endif

// card_list.h
// Author: Henry Li
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

class CardBST {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c) : card(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void clear(Node* n);
    bool insert(const Card& card, Node* n);
    Node* getNodeFor(const Card& card, Node* n) const;
    void printInOrder(Node* n, std::ostream& os) const;

public:
    class Iterator {
    public:
        const Card& operator*() const;
        const Card* operator->() const;
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* current;
        Iterator(Node* n = nullptr);
        friend class CardBST;
    };

    CardBST();
    ~CardBST();

    bool insert(const Card& card);
    bool remove(const Card& card);
    bool contains(const Card& card) const;
    void printInOrder(std::ostream& os = std::cout) const;
    bool isEmpty() const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

void playGame(CardBST& alice, CardBST& bob);

#endif

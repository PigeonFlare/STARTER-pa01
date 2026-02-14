// card_list.cpp
// Author: Henry Li
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

using namespace std;

// Constructor
CardBST::CardBST() : root(nullptr) {}

// Destructor
CardBST::~CardBST()
{
    clear(root);
}

// Recursive helper for destructor
void CardBST::clear(Node *n)
{
    if (!n)
        return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// Insert a card; return false if duplicate
bool CardBST::insert(const Card &card)
{
    if (!root)
    {
        root = new Node(card);
        return true;
    }
    return insert(card, root);
}

// Recursive helper for insert
bool CardBST::insert(const Card &card, Node *n)
{
    if (card == n->card)
        return false;
    if (card < n->card)
    {
        if (!n->left)
        {
            n->left = new Node(card);
            n->left->parent = n;
            return true;
        }
        return insert(card, n->left);
    }
    else
    {
        if (!n->right)
        {
            n->right = new Node(card);
            n->right->parent = n;
            return true;
        }
        return insert(card, n->right);
    }
}

// Find node for a given card
CardBST::Node *CardBST::getNodeFor(const Card &card, Node *n) const
{
    if (!n)
        return nullptr;
    if (card == n->card)
        return n;
    if (card < n->card)
        return getNodeFor(card, n->left);
    return getNodeFor(card, n->right);
}

// Check if tree contains a card
bool CardBST::contains(const Card &card) const
{
    return getNodeFor(card, root) != nullptr;
}

// Remove a card from the tree
bool CardBST::remove(const Card &card)
{
    Node *n = getNodeFor(card, root);
    if (!n)
        return false;

    // Leaf node
    if (!n->left && !n->right)
    {
        if (!n->parent)
        {
            root = nullptr;
        }
        else
        {
            if (n->parent->left == n)
                n->parent->left = nullptr;
            else
                n->parent->right = nullptr;
        }
        delete n;
        return true;
    }

    // One child
    if (!n->left || !n->right)
    {
        Node *child = n->left ? n->left : n->right;
        child->parent = n->parent;
        if (!n->parent)
        {
            root = child;
        }
        else
        {
            if (n->parent->left == n)
                n->parent->left = child;
            else
                n->parent->right = child;
        }
        delete n;
        return true;
    }

    // Two children: find in-order successor (smallest in right subtree)
    Node *succ = n->right;
    while (succ->left)
        succ = succ->left;
    Card succCard = succ->card;
    remove(succCard); // successor has at most one child
    n->card = succCard;
    return true;
}

// Print all cards in order
void CardBST::printInOrder(ostream &os) const
{
    printInOrder(root, os);
}

void CardBST::printInOrder(Node *n, ostream &os) const
{
    if (!n)
        return;
    printInOrder(n->left, os);
    os << n->card << endl;
    printInOrder(n->right, os);
}

// Check if tree is empty
bool CardBST::isEmpty() const
{
    return root == nullptr;
}

// Iterator: begin (smallest element)
CardBST::Iterator CardBST::begin() const
{
    if (!root)
        return Iterator(nullptr);
    Node *n = root;
    while (n->left)
        n = n->left;
    return Iterator(n);
}

// Iterator: end (past the largest)
CardBST::Iterator CardBST::end() const
{
    return Iterator(nullptr);
}

// Iterator: rbegin (largest element)
CardBST::Iterator CardBST::rbegin() const
{
    if (!root)
        return Iterator(nullptr);
    Node *n = root;
    while (n->right)
        n = n->right;
    return Iterator(n);
}

// Iterator: rend (before the smallest)
CardBST::Iterator CardBST::rend() const
{
    return Iterator(nullptr);
}

// ---- Iterator implementation ----

CardBST::Iterator::Iterator(Node *n) : current(n) {}

const Card &CardBST::Iterator::operator*() const
{
    return current->card;
}

const Card *CardBST::Iterator::operator->() const
{
    return &(current->card);
}

// Move to in-order successor
CardBST::Iterator &CardBST::Iterator::operator++()
{
    if (!current)
        return *this;
    if (current->right)
    {
        current = current->right;
        while (current->left)
            current = current->left;
    }
    else
    {
        Node *p = current->parent;
        while (p && current == p->right)
        {
            current = p;
            p = p->parent;
        }
        current = p;
    }
    return *this;
}

// Move to in-order predecessor
CardBST::Iterator &CardBST::Iterator::operator--()
{
    if (!current)
        return *this;
    if (current->left)
    {
        current = current->left;
        while (current->right)
            current = current->right;
    }
    else
    {
        Node *p = current->parent;
        while (p && current == p->left)
        {
            current = p;
            p = p->parent;
        }
        current = p;
    }
    return *this;
}

bool CardBST::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}

bool CardBST::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}

// ---- playGame function ----

void playGame(CardBST &alice, CardBST &bob)
{
    while (true)
    {
        // Alice's turn - forward (smallest to largest)
        bool found = false;
        for (auto it = alice.begin(); it != alice.end(); ++it)
        {
            if (bob.contains(*it))
            {
                Card card = *it;
                cout << "Alice picked matching card " << card << endl;
                alice.remove(card);
                bob.remove(card);
                found = true;
                break;
            }
        }
        if (!found)
            break;

        // Bob's turn - reverse (largest to smallest)
        found = false;
        for (auto it = bob.rbegin(); it != bob.rend(); --it)
        {
            if (alice.contains(*it))
            {
                Card card = *it;
                cout << "Bob picked matching card " << card << endl;
                alice.remove(card);
                bob.remove(card);
                found = true;
                break;
            }
        }
        if (!found)
            break;
    }

    // Print remaining hands
    cout << endl;
    cout << "Alice's cards:" << endl;
    for (auto it = alice.begin(); it != alice.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl;
    cout << "Bob's cards:" << endl;
    for (auto it = bob.begin(); it != bob.end(); ++it)
    {
        cout << *it << endl;
    }
}

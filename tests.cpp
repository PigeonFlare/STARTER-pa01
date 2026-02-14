// tests.cpp
// Author: Henry Li
// Test cases for Card, CardBST, Iterator, and playGame

#include <iostream>
#include <sstream>
#include <cassert>
#include "card.h"
#include "card_list.h"

using namespace std;

int testsPassed = 0;
int testsFailed = 0;

void check(bool condition, const string& testName) {
    if (condition) {
        cout << "  PASS: " << testName << endl;
        testsPassed++;
    } else {
        cout << "  FAIL: " << testName << endl;
        testsFailed++;
    }
}

// ========== Card Comparison Tests ==========
void testCardComparison() {
    cout << "=== Card Comparison Tests ===" << endl;

    Card ca('c', 1);   // clubs ace
    Card c3('c', 3);   // clubs 3
    Card ck('c', 13);  // clubs king
    Card d3('d', 3);   // diamonds 3
    Card s3('s', 3);   // spades 3
    Card h9('h', 9);   // hearts 9
    Card hj('h', 11);  // hearts jack

    // Suit ordering: c < d < s < h
    check(ca < d3, "clubs ace < diamonds 3");
    check(ck < d3, "clubs king < diamonds 3 (suit priority)");
    check(d3 < s3, "diamonds 3 < spades 3");
    check(s3 < h9, "spades 3 < hearts 9");

    // Value ordering within same suit
    check(ca < c3, "clubs ace < clubs 3");
    check(c3 < ck, "clubs 3 < clubs king");
    check(h9 < hj, "hearts 9 < hearts jack");

    // Equality
    Card ca2('c', 1);
    check(ca == ca2, "clubs ace == clubs ace (copy)");
    check(!(ca == c3), "clubs ace != clubs 3");
    check(ca != c3, "operator!= works");

    // Greater than
    check(d3 > ca, "diamonds 3 > clubs ace");
    check(ck > ca, "clubs king > clubs ace");

    // operator<< output
    ostringstream oss;
    oss << ca;
    check(oss.str() == "c a", "operator<< ace");
    oss.str("");
    oss << Card('h', 10);
    check(oss.str() == "h 10", "operator<< 10");
    oss.str("");
    oss << Card('d', 11);
    check(oss.str() == "d j", "operator<< jack");
    oss.str("");
    oss << Card('s', 12);
    check(oss.str() == "s q", "operator<< queen");
    oss.str("");
    oss << Card('c', 13);
    check(oss.str() == "c k", "operator<< king");
}

// ========== BST Insert Tests ==========
void testInsert() {
    cout << "\n=== BST Insert Tests ===" << endl;

    // Test 1: Insert into empty tree
    CardBST bst;
    check(bst.insert(Card('c', 1)), "Insert into empty tree returns true");
    check(!bst.isEmpty(), "Tree not empty after insert");

    // Test 2: Insert multiple cards
    check(bst.insert(Card('d', 5)), "Insert second card");
    check(bst.insert(Card('h', 10)), "Insert third card");

    // Test 3: Insert duplicate returns false
    check(!bst.insert(Card('c', 1)), "Duplicate insert returns false");

    // Test 4: Insert in sorted order
    CardBST bst2;
    bst2.insert(Card('c', 1));
    bst2.insert(Card('c', 5));
    bst2.insert(Card('c', 10));
    bst2.insert(Card('d', 3));
    bst2.insert(Card('h', 13));
    ostringstream oss;
    bst2.printInOrder(oss);
    check(oss.str() == "c a\nc 5\nc 10\nd 3\nh k\n",
          "Insert maintains BST order");

    // Test 5: Insert cards in reverse order
    CardBST bst3;
    bst3.insert(Card('h', 13));
    bst3.insert(Card('d', 3));
    bst3.insert(Card('c', 10));
    bst3.insert(Card('c', 5));
    bst3.insert(Card('c', 1));
    ostringstream oss2;
    bst3.printInOrder(oss2);
    check(oss2.str() == "c a\nc 5\nc 10\nd 3\nh k\n",
          "Reverse-order insert maintains BST order");

    // Test 6: Insert single card
    CardBST bst4;
    bst4.insert(Card('s', 7));
    ostringstream oss3;
    bst4.printInOrder(oss3);
    check(oss3.str() == "s 7\n", "Single card print");
}

// ========== BST Contains Tests ==========
void testContains() {
    cout << "\n=== BST Contains Tests ===" << endl;

    // Test 1: Empty tree
    CardBST bst;
    check(!bst.contains(Card('c', 1)), "Contains on empty tree returns false");

    // Test 2: Single element - found
    bst.insert(Card('c', 1));
    check(bst.contains(Card('c', 1)), "Contains finds inserted card");

    // Test 3: Single element - not found
    check(!bst.contains(Card('d', 5)), "Contains returns false for absent card");

    // Test 4: Multiple elements
    bst.insert(Card('d', 5));
    bst.insert(Card('h', 10));
    bst.insert(Card('s', 3));
    check(bst.contains(Card('h', 10)), "Contains finds card in larger tree");
    check(bst.contains(Card('s', 3)), "Contains finds another card");

    // Test 5: Contains after removal
    bst.remove(Card('d', 5));
    check(!bst.contains(Card('d', 5)), "Contains returns false after removal");

    // Test 6: Card with same value different suit
    bst.insert(Card('d', 3));
    check(bst.contains(Card('s', 3)), "Contains spades 3");
    check(bst.contains(Card('d', 3)), "Contains diamonds 3");
    check(!bst.contains(Card('c', 3)), "Does not contain clubs 3");
}

// ========== BST Remove Tests ==========
void testRemove() {
    cout << "\n=== BST Remove Tests ===" << endl;

    // Test 1: Remove from empty tree
    CardBST bst;
    check(!bst.remove(Card('c', 1)), "Remove from empty tree returns false");

    // Test 2: Remove non-existent card
    bst.insert(Card('c', 1));
    check(!bst.remove(Card('d', 5)), "Remove non-existent returns false");

    // Test 3: Remove leaf node
    bst.insert(Card('d', 5));
    bst.insert(Card('h', 10));
    check(bst.remove(Card('h', 10)), "Remove leaf returns true");
    check(!bst.contains(Card('h', 10)), "Removed leaf no longer in tree");

    // Test 4: Remove node with one child
    CardBST bst2;
    bst2.insert(Card('d', 5));
    bst2.insert(Card('c', 3));
    bst2.insert(Card('c', 1));  // c 3 has left child c 1
    check(bst2.remove(Card('c', 3)), "Remove node with one child");
    check(bst2.contains(Card('c', 1)), "Child still in tree after parent removed");
    check(bst2.contains(Card('d', 5)), "Root still in tree");

    // Test 5: Remove node with two children
    CardBST bst3;
    bst3.insert(Card('d', 5));
    bst3.insert(Card('c', 3));
    bst3.insert(Card('h', 10));
    check(bst3.remove(Card('d', 5)), "Remove node with two children");
    check(!bst3.contains(Card('d', 5)), "Removed node gone");
    check(bst3.contains(Card('c', 3)), "Left child still present");
    check(bst3.contains(Card('h', 10)), "Right child still present");

    // Test 6: Remove root (only element)
    CardBST bst4;
    bst4.insert(Card('s', 7));
    check(bst4.remove(Card('s', 7)), "Remove single root");
    check(bst4.isEmpty(), "Tree empty after removing only element");

    // Test 7: Remove all elements
    CardBST bst5;
    bst5.insert(Card('c', 1));
    bst5.insert(Card('d', 5));
    bst5.insert(Card('h', 10));
    bst5.remove(Card('c', 1));
    bst5.remove(Card('d', 5));
    bst5.remove(Card('h', 10));
    check(bst5.isEmpty(), "Tree empty after removing all elements");
}

// ========== BST Print Tests ==========
void testPrint() {
    cout << "\n=== BST Print Tests ===" << endl;

    // Test 1: Empty tree
    CardBST bst;
    ostringstream oss;
    bst.printInOrder(oss);
    check(oss.str() == "", "Print empty tree gives empty string");

    // Test 2: Single card
    bst.insert(Card('c', 1));
    oss.str("");
    bst.printInOrder(oss);
    check(oss.str() == "c a\n", "Print single card");

    // Test 3: Multiple cards in order
    bst.insert(Card('d', 5));
    bst.insert(Card('h', 10));
    oss.str("");
    bst.printInOrder(oss);
    check(oss.str() == "c a\nd 5\nh 10\n", "Print multiple cards in order");

    // Test 4: Cards with 10 value
    CardBST bst2;
    bst2.insert(Card('c', 10));
    bst2.insert(Card('s', 10));
    bst2.insert(Card('h', 10));
    oss.str("");
    bst2.printInOrder(oss);
    check(oss.str() == "c 10\ns 10\nh 10\n", "Print cards with value 10");

    // Test 5: All face cards
    CardBST bst3;
    bst3.insert(Card('c', 11));  // jack
    bst3.insert(Card('d', 12));  // queen
    bst3.insert(Card('s', 13));  // king
    bst3.insert(Card('h', 1));   // ace
    oss.str("");
    bst3.printInOrder(oss);
    check(oss.str() == "c j\nd q\ns k\nh a\n", "Print face cards");

    // Test 6: After removal
    CardBST bst4;
    bst4.insert(Card('c', 1));
    bst4.insert(Card('d', 5));
    bst4.insert(Card('h', 10));
    bst4.remove(Card('d', 5));
    oss.str("");
    bst4.printInOrder(oss);
    check(oss.str() == "c a\nh 10\n", "Print after removal");
}

// ========== Iterator Tests ==========
void testIterator() {
    cout << "\n=== Iterator Tests ===" << endl;

    // Test 1: Empty tree - begin == end
    CardBST bst;
    check(bst.begin() == bst.end(), "Empty tree: begin == end");
    check(bst.rbegin() == bst.rend(), "Empty tree: rbegin == rend");

    // Test 2: Single node
    bst.insert(Card('d', 5));
    auto it = bst.begin();
    check(*it == Card('d', 5), "Single node: begin dereference");
    ++it;
    check(it == bst.end(), "Single node: ++begin == end");

    auto rit = bst.rbegin();
    check(*rit == Card('d', 5), "Single node: rbegin dereference");
    --rit;
    check(rit == bst.rend(), "Single node: --rbegin == rend");

    // Test 3: Multiple nodes - forward traversal
    CardBST bst2;
    bst2.insert(Card('d', 5));
    bst2.insert(Card('c', 1));
    bst2.insert(Card('h', 10));
    bst2.insert(Card('s', 3));
    bst2.insert(Card('c', 13));

    string forward = "";
    for (auto it2 = bst2.begin(); it2 != bst2.end(); ++it2) {
        ostringstream oss;
        oss << *it2;
        forward += oss.str() + " ";
    }
    check(forward == "c a c k d 5 s 3 h 10 ", "Forward traversal order");

    // Test 4: Multiple nodes - reverse traversal
    string reverse = "";
    for (auto it2 = bst2.rbegin(); it2 != bst2.rend(); --it2) {
        ostringstream oss;
        oss << *it2;
        reverse += oss.str() + " ";
    }
    check(reverse == "h 10 s 3 d 5 c k c a ", "Reverse traversal order");

    // Test 5: Iterator comparison
    auto it1 = bst2.begin();
    auto it2 = bst2.begin();
    check(it1 == it2, "Two begin iterators are equal");
    ++it1;
    check(it1 != it2, "After ++, iterators are not equal");

    // Test 6: operator-> access
    CardBST bst3;
    bst3.insert(Card('h', 10));
    auto it3 = bst3.begin();
    check(it3->getSuit() == 'h', "operator-> getSuit");
    check(it3->getValue() == 10, "operator-> getValue");

    // Test 7: Increment past end is safe
    CardBST bst4;
    bst4.insert(Card('c', 1));
    auto it4 = bst4.begin();
    ++it4;  // now at end
    ++it4;  // past end, should not crash
    check(it4 == bst4.end(), "Increment past end stays at end");

    // Test 8: Decrement past rend is safe
    auto it5 = bst4.rbegin();
    --it5;  // now at rend
    --it5;  // past rend, should not crash
    check(it5 == bst4.rend(), "Decrement past rend stays at rend");
}

// ========== playGame Tests ==========
void testPlayGame() {
    cout << "\n=== playGame Tests ===" << endl;

    // Test 1: Both players with common cards (main example)
    {
        CardBST alice, bob;
        // Alice: h 3, s 10, c a, c 3, s 5, h 10, d a
        alice.insert(Card('h', 3));
        alice.insert(Card('s', 10));
        alice.insert(Card('c', 1));
        alice.insert(Card('c', 3));
        alice.insert(Card('s', 5));
        alice.insert(Card('h', 10));
        alice.insert(Card('d', 1));

        // Bob: c 2, d a, h 10, c 3, d j, s 10, h a
        bob.insert(Card('c', 2));
        bob.insert(Card('d', 1));
        bob.insert(Card('h', 10));
        bob.insert(Card('c', 3));
        bob.insert(Card('d', 11));
        bob.insert(Card('s', 10));
        bob.insert(Card('h', 1));

        // Capture output
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        playGame(alice, bob);
        cout.rdbuf(old);

        string expected =
            "Alice picked matching card c 3\n"
            "Bob picked matching card h 10\n"
            "Alice picked matching card d a\n"
            "Bob picked matching card s 10\n"
            "\n"
            "Alice's cards:\n"
            "c a\n"
            "s 5\n"
            "h 3\n"
            "\n"
            "Bob's cards:\n"
            "c 2\n"
            "d j\n"
            "h a\n";

        check(oss.str() == expected, "Main example game output matches");
    }

    // Test 2: No common cards
    {
        CardBST alice, bob;
        alice.insert(Card('c', 11));  // c j
        alice.insert(Card('s', 10));

        bob.insert(Card('c', 9));
        bob.insert(Card('d', 2));

        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        playGame(alice, bob);
        cout.rdbuf(old);

        string expected =
            "\n"
            "Alice's cards:\n"
            "c j\n"
            "s 10\n"
            "\n"
            "Bob's cards:\n"
            "c 9\n"
            "d 2\n";

        check(oss.str() == expected, "No common cards game output");
    }

    // Test 3: One empty hand
    {
        CardBST alice, bob;
        alice.insert(Card('c', 1));
        alice.insert(Card('d', 5));
        // bob is empty

        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        playGame(alice, bob);
        cout.rdbuf(old);

        string expected =
            "\n"
            "Alice's cards:\n"
            "c a\n"
            "d 5\n"
            "\n"
            "Bob's cards:\n";

        check(oss.str() == expected, "One empty hand game output");
    }

    // Test 4: All cards match (Alice ends game, odd number of common)
    {
        CardBST alice, bob;
        alice.insert(Card('c', 1));
        alice.insert(Card('d', 5));
        alice.insert(Card('h', 10));

        bob.insert(Card('c', 1));
        bob.insert(Card('d', 5));
        bob.insert(Card('h', 10));

        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        playGame(alice, bob);
        cout.rdbuf(old);

        string expected =
            "Alice picked matching card c a\n"
            "Bob picked matching card h 10\n"
            "Alice picked matching card d 5\n"
            "\n"
            "Alice's cards:\n"
            "\n"
            "Bob's cards:\n";

        check(oss.str() == expected, "All cards match game output");
    }
}

int main() {
    testCardComparison();
    testInsert();
    testContains();
    testRemove();
    testPrint();
    testIterator();
    testPlayGame();

    cout << "\n=============================" << endl;
    cout << "Results: " << testsPassed << " passed, " << testsFailed << " failed" << endl;

    return testsFailed > 0 ? 1 : 0;
}

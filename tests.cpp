#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "card.h"
#include "card_list.h"

using namespace std;

static Card makeCard(char suit, const string& rank) {
  return Card(suit, rank);
}

static string cardToString(const Card& card) {
  ostringstream os;
  os << card;
  return os.str();
}

static string inOrderString(const CardBST& tree) {
  ostringstream os;
  tree.printInOrder(os);
  return os.str();
}

static vector<string> forwardTraversal(const CardBST& tree) {
  vector<string> values;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    values.push_back(cardToString(*it));
  }
  return values;
}

static vector<string> reverseTraversal(const CardBST& tree) {
  vector<string> values;
  for (auto it = tree.rbegin(); it != tree.rend(); --it) {
    values.push_back(cardToString(*it));
  }
  return values;
}

void testInsert() {
  CardBST tree;

  tree.insert(makeCard('h', "3"));
  assert(tree.contains(makeCard('h', "3")));

  tree.insert(makeCard('c', "a"));
  tree.insert(makeCard('s', "10"));
  tree.insert(makeCard('d', "j"));
  assert(tree.contains(makeCard('c', "a")));
  assert(tree.contains(makeCard('s', "10")));
  assert(tree.contains(makeCard('d', "j")));

  string beforeDup = inOrderString(tree);
  tree.insert(makeCard('d', "j"));
  string afterDup = inOrderString(tree);
  assert(beforeDup == afterDup);

  tree.insert(makeCard('h', "k"));
  tree.insert(makeCard('c', "2"));
  assert(tree.contains(makeCard('h', "k")));
  assert(tree.contains(makeCard('c', "2")));
}

void testContains() {
  CardBST tree;

  assert(!tree.contains(makeCard('c', "a")));

  tree.insert(makeCard('c', "a"));
  assert(tree.contains(makeCard('c', "a")));

  assert(!tree.contains(makeCard('c', "2")));

  tree.insert(makeCard('d', "10"));
  tree.insert(makeCard('s', "q"));
  tree.insert(makeCard('h', "5"));
  assert(tree.contains(makeCard('d', "10")));
  assert(tree.contains(makeCard('s', "q")));

  tree.remove(makeCard('d', "10"));
  assert(!tree.contains(makeCard('d', "10")));
}

void testRemove() {
  CardBST tree;

  tree.remove(makeCard('c', "a"));
  assert(tree.empty());

  tree.insert(makeCard('d', "5"));
  tree.remove(makeCard('d', "5"));
  assert(tree.empty());

  tree.insert(makeCard('d', "5"));
  tree.insert(makeCard('c', "a"));
  tree.insert(makeCard('c', "2"));
  tree.remove(makeCard('c', "a"));
  assert(!tree.contains(makeCard('c', "a")));
  assert(tree.contains(makeCard('c', "2")));

  tree.insert(makeCard('h', "9"));
  tree.insert(makeCard('s', "k"));
  tree.insert(makeCard('h', "j"));
  tree.remove(makeCard('h', "9"));
  assert(!tree.contains(makeCard('h', "9")));

  tree.remove(makeCard('d', "5"));
  assert(!tree.contains(makeCard('d', "5")));

  string sorted = inOrderString(tree);
  assert(sorted == "c 2\ns k\nh j\n");
}

void testPrintInOrder() {
  CardBST tree;

  assert(inOrderString(tree) == "");

  tree.insert(makeCard('h', "10"));
  assert(inOrderString(tree) == "h 10\n");

  tree.insert(makeCard('c', "3"));
  tree.insert(makeCard('d', "a"));
  tree.insert(makeCard('s', "10"));
  assert(inOrderString(tree) == "c 3\nd a\ns 10\nh 10\n");

  tree.remove(makeCard('d', "a"));
  assert(inOrderString(tree) == "c 3\ns 10\nh 10\n");

  tree.insert(makeCard('c', "a"));
  tree.insert(makeCard('h', "k"));
  assert(inOrderString(tree) == "c a\nc 3\ns 10\nh 10\nh k\n");
}

void testIterators() {
  CardBST tree;

  assert(tree.begin() == tree.end());
  assert(tree.rbegin() == tree.rend());

  tree.insert(makeCard('d', "7"));
  auto itSingle = tree.begin();
  assert(cardToString(*itSingle) == "d 7");
  ++itSingle;
  assert(itSingle == tree.end());

  auto ritSingle = tree.rbegin();
  assert(cardToString(*ritSingle) == "d 7");
  --ritSingle;
  assert(ritSingle == tree.rend());

  CardBST multi;
  multi.insert(makeCard('h', "3"));
  multi.insert(makeCard('c', "a"));
  multi.insert(makeCard('s', "10"));
  multi.insert(makeCard('c', "3"));
  multi.insert(makeCard('d', "a"));

  vector<string> expectedForward = {"c a", "c 3", "d a", "s 10", "h 3"};
  vector<string> expectedReverse = {"h 3", "s 10", "d a", "c 3", "c a"};
  assert(forwardTraversal(multi) == expectedForward);
  assert(reverseTraversal(multi) == expectedReverse);

  auto endIt = multi.end();
  ++endIt;
  assert(endIt == multi.end());

  auto rendIt = multi.rend();
  --rendIt;
  assert(rendIt == multi.rend());

  auto a = multi.begin();
  auto b = multi.begin();
  assert(a == b);
  ++b;
  assert(a != b);
}

void testPlayGame() {
  {
    CardBST alice;
    CardBST bob;

    alice.insert(makeCard('h', "3"));
    alice.insert(makeCard('s', "10"));
    alice.insert(makeCard('c', "a"));
    alice.insert(makeCard('c', "3"));
    alice.insert(makeCard('s', "5"));
    alice.insert(makeCard('h', "10"));
    alice.insert(makeCard('d', "a"));

    bob.insert(makeCard('c', "2"));
    bob.insert(makeCard('d', "a"));
    bob.insert(makeCard('h', "10"));
    bob.insert(makeCard('c', "3"));
    bob.insert(makeCard('d', "j"));
    bob.insert(makeCard('s', "10"));
    bob.insert(makeCard('h', "a"));

    ostringstream os;
    playGame(alice, bob, os);

    string expected =
        "Alice picked matching card c 3\n"
        "Bob picked matching card h 10\n"
        "Alice picked matching card d a\n"
        "Bob picked matching card s 10\n";
    assert(os.str() == expected);

    assert(inOrderString(alice) == "c a\ns 5\nh 3\n");
    assert(inOrderString(bob) == "c 2\nd j\nh a\n");
  }

  {
    CardBST alice;
    CardBST bob;

    bob.insert(makeCard('c', "2"));
    bob.insert(makeCard('h', "k"));

    ostringstream os;
    playGame(alice, bob, os);

    assert(os.str().empty());
    assert(inOrderString(alice).empty());
    assert(inOrderString(bob) == "c 2\nh k\n");
  }

  {
    CardBST alice;
    CardBST bob;

    alice.insert(makeCard('c', "a"));
    alice.insert(makeCard('d', "2"));
    bob.insert(makeCard('s', "3"));
    bob.insert(makeCard('h', "4"));

    ostringstream os;
    playGame(alice, bob, os);

    assert(os.str().empty());
    assert(inOrderString(alice) == "c a\nd 2\n");
    assert(inOrderString(bob) == "s 3\nh 4\n");
  }
}

int main() {
  testInsert();
  testContains();
  testRemove();
  testPrintInOrder();
  testIterators();
  testPlayGame();

  cout << "All tests passed" << endl;
  return 0;
}

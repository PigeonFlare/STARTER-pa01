// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

static void printHands(const set<Card> &alice, const set<Card> &bob)
{
  cout << "\nAlice's cards:" << endl;
  for (const Card &card : alice)
  {
    cout << card << endl;
  }

  cout << "\nBob's cards:" << endl;
  for (const Card &card : bob)
  {
    cout << card << endl;
  }
}

int main(int argv, char **argc)
{
  if (argv < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> alice;
  set<Card> bob;

  // Read each file
  char suit;
  string rank;
  while (cardFile1 >> suit >> rank)
  {
    alice.insert(Card(suit, rank));
  }
  cardFile1.close();

  while (cardFile2 >> suit >> rank)
  {
    bob.insert(Card(suit, rank));
  }
  cardFile2.close();

  while (true)
  {
    bool aliceMatched = false;
    for (auto it = alice.begin(); it != alice.end(); ++it)
    {
      const Card current = *it;
      if (bob.find(current) != bob.end())
      {
        cout << "Alice picked matching card " << current << endl;
        alice.erase(current);
        bob.erase(current);
        aliceMatched = true;
        break;
      }
    }

    if (!aliceMatched)
    {
      break;
    }

    bool bobMatched = false;
    for (auto it = bob.rbegin(); it != bob.rend(); ++it)
    {
      const Card current = *it;
      if (alice.find(current) != alice.end())
      {
        cout << "Bob picked matching card " << current << endl;
        alice.erase(current);
        bob.erase(current);
        bobMatched = true;
        break;
      }
    }

    if (!bobMatched)
    {
      break;
    }
  }

  printHands(alice, bob);

  return 0;
}

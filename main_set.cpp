// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char **argc)
{
  if (argv < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> alice, bob;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    istringstream iss(line);
    Card c;
    iss >> c;
    alice.insert(c);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0))
  {
    istringstream iss(line);
    Card c;
    iss >> c;
    bob.insert(c);
  }
  cardFile2.close();

  // Play the game
  while (true)
  {
    // Alice's turn - forward (smallest to largest)
    bool found = false;
    for (auto it = alice.begin(); it != alice.end(); ++it)
    {
      if (bob.count(*it))
      {
        Card card = *it;
        cout << "Alice picked matching card " << card << endl;
        alice.erase(card);
        bob.erase(card);
        found = true;
        break;
      }
    }
    if (!found) break;

    // Bob's turn - reverse (largest to smallest)
    found = false;
    for (auto it = bob.rbegin(); it != bob.rend(); ++it)
    {
      if (alice.count(*it))
      {
        Card card = *it;
        cout << "Bob picked matching card " << card << endl;
        alice.erase(card);
        bob.erase(card);
        found = true;
        break;
      }
    }
    if (!found) break;
  }

  // Print remaining hands
  cout << endl;
  cout << "Alice's cards:" << endl;
  for (const auto &card : alice)
  {
    cout << card << endl;
  }

  cout << endl;
  cout << "Bob's cards:" << endl;
  for (const auto &card : bob)
  {
    cout << card << endl;
  }

  return 0;
}

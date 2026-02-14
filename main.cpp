// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

static void printHands(const CardBST& alice, const CardBST& bob) {
  cout << "\nAlice's cards:" << endl;
  alice.printInOrder(cout);

  cout << "\nBob's cards:" << endl;
  bob.printInOrder(cout);
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardBST alice;
  CardBST bob;

  //Read each file
  char suit;
  string rank;
  while (cardFile1 >> suit >> rank){
    alice.insert(Card(suit, rank));
  }
  cardFile1.close();


  while (cardFile2 >> suit >> rank){
    bob.insert(Card(suit, rank));
  }
  cardFile2.close();

  playGame(alice, bob, cout);
  printHands(alice, bob);
  
  
  return 0;
}

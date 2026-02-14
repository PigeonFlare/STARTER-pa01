// card.h
// Author: Henry Li
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
public:
    Card();
    Card(char suit, int value);

    char getSuit() const;
    int getValue() const;

    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator<=(const Card& other) const;
    bool operator>=(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend std::istream& operator>>(std::istream& is, Card& card);

private:
    char suit_;  // 'c', 'd', 's', 'h'
    int value_;  // 1=ace, 2-10, 11=jack, 12=queen, 13=king

    static int suitRank(char s);
};

#endif

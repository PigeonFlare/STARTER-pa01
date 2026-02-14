// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card
{
public:
    Card();
    Card(char suit, const std::string &rank);

    char getSuit() const;
    const std::string &getRank() const;

    bool operator==(const Card &other) const;
    bool operator<(const Card &other) const;
    bool operator>(const Card &other) const;

private:
    char suit;
    std::string rank;
};

std::ostream &operator<<(std::ostream &os, const Card &card);

#endif

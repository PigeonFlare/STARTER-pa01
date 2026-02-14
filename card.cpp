// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"

using namespace std;

namespace
{
    int suitOrder(char suit)
    {
        switch (suit)
        {
        case 'c':
            return 0;
        case 'd':
            return 1;
        case 's':
            return 2;
        case 'h':
            return 3;
        default:
            return 4;
        }
    }

    int rankOrder(const string &rank)
    {
        if (rank == "a")
            return 1;
        if (rank == "j")
            return 11;
        if (rank == "q")
            return 12;
        if (rank == "k")
            return 13;
        return stoi(rank);
    }
}

Card::Card() : suit('c'), rank("a") {}

Card::Card(char suit, const string &rank) : suit(suit), rank(rank) {}

char Card::getSuit() const
{
    return suit;
}

const string &Card::getRank() const
{
    return rank;
}

bool Card::operator==(const Card &other) const
{
    return suit == other.suit && rank == other.rank;
}

bool Card::operator<(const Card &other) const
{
    int thisSuit = suitOrder(suit);
    int otherSuit = suitOrder(other.suit);
    if (thisSuit != otherSuit)
    {
        return thisSuit < otherSuit;
    }
    return rankOrder(rank) < rankOrder(other.rank);
}

bool Card::operator>(const Card &other) const
{
    return other < *this;
}

ostream &operator<<(ostream &os, const Card &card)
{
    os << card.getSuit() << " " << card.getRank();
    return os;
}

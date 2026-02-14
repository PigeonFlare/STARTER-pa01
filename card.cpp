// card.cpp
// Author: Henry Li
// Implementation of the classes defined in card.h

#include "card.h"
#include <string>

Card::Card() : suit_('c'), value_(1) {}

Card::Card(char suit, int value) : suit_(suit), value_(value) {}

char Card::getSuit() const { return suit_; }
int Card::getValue() const { return value_; }

int Card::suitRank(char s) {
    switch (s) {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default: return -1;
    }
}

bool Card::operator==(const Card& other) const {
    return suit_ == other.suit_ && value_ == other.value_;
}

bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

bool Card::operator<(const Card& other) const {
    if (suitRank(suit_) != suitRank(other.suit_))
        return suitRank(suit_) < suitRank(other.suit_);
    return value_ < other.value_;
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator<=(const Card& other) const {
    return !(other < *this);
}

bool Card::operator>=(const Card& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit_ << " ";
    switch (card.value_) {
        case 1:  os << "a"; break;
        case 11: os << "j"; break;
        case 12: os << "q"; break;
        case 13: os << "k"; break;
        default: os << card.value_; break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Card& card) {
    char suit;
    std::string val;
    if (is >> suit >> val) {
        card.suit_ = suit;
        if (val == "a") card.value_ = 1;
        else if (val == "j") card.value_ = 11;
        else if (val == "q") card.value_ = 12;
        else if (val == "k") card.value_ = 13;
        else card.value_ = std::stoi(val);
    }
    return is;
}

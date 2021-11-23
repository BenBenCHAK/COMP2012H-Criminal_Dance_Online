#ifndef BARTER_H
#define BARTER_H

#include "Card.h"

class Barter : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
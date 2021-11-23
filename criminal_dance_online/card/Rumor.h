#ifndef RUMOR_H
#define RUMOR_H

#include "Card.h"

class Rumor : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
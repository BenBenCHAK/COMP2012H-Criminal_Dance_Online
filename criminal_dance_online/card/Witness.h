#ifndef WITNESS_H
#define WITNESS_H

#include "Card.h"

class Witness : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
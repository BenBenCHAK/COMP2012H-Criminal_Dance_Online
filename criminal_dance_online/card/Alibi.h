#ifndef ALIBI_H
#define ALIBI_H

#include "Card.h"

class Alibi : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
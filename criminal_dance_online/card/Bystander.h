#ifndef BYSTANDER_H
#define BYSTANDER_H

#include "Card.h"

class Bystander : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
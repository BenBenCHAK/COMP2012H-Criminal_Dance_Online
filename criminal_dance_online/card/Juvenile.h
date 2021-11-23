#ifndef JUVENILE_H
#define JUVENILE_H

#include "Card.h"

class Juvenile : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
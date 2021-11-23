#ifndef BASTET_H
#define BASTET_H

#include "Card.h"

class Bastet : public Card{  // God Dog
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
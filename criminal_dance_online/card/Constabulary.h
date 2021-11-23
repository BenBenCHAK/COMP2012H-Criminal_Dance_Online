#ifndef CONSTABULARY_H
#define CONSTABULARY_H

#include "Card.h"

class Constabulary : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
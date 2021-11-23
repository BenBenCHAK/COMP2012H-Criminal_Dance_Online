#ifndef CULPRIT_H
#define CULPRIT_H

#include "Card.h"

class Culprit : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
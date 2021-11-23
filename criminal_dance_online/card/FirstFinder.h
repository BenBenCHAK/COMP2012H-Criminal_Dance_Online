#ifndef FIRSTFINDER_H
#define FIRSTFINDER_H

#include "Card.h"

class FirstFinder : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
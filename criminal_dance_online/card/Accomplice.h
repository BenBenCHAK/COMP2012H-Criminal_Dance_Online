#ifndef ACCOMPLICE_H
#define ACCOMPLICE_H

#include "Card.h"

class Accomplice : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
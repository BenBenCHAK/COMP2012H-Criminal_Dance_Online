#ifndef DETECTIVE_H
#define DETECTIVE_H

#include "Card.h"

class Detective : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;

    bool check_culprit() const;
};

#endif
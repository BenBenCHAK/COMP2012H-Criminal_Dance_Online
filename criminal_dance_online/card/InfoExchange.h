#ifndef INFOEXCHANGE_H
#define INFOEXCHANGE_H

#include "Card.h"

class InfoExchange : public Card{
public:
    Card::CardType get_type() const;
    bool use() const;
};

#endif
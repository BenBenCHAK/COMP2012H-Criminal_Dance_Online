#include "Rumor.h"
#include "../Card.h"

Card::CardType Rumor::get_type() const{
    return Card::CardType::RUMOR;
}
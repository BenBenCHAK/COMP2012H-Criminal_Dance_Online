#include "Witness.h"
#include "../Card.h"

Card::CardType Witness::get_type() const{
    return Card::CardType::WITNESS;
}
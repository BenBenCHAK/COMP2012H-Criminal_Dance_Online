#include "Bystander.h"
#include "../Card.h"

Card::CardType Bystander::get_type() const{
    return Card::CardType::BYSTANDER;
}
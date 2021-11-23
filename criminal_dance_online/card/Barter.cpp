#include "Barter.h"
#include "../Card.h"

Card::CardType Barter::get_type() const{
    return Card::CardType::BARTER;
}
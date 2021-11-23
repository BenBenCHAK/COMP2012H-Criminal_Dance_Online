#include "Detective.h"
#include "../Card.h"

Card::CardType Detective::get_type() const{
    return Card::CardType::DETECTIVE;
}

bool Detective::check_culprit(Player *target) const{
    if (target->getPlayerType() == Player::PlayerType::CIVILIAN) 
        return false;
    return true;
}

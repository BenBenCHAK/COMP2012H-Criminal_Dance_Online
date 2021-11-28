#include "Card.h"

Card::Card(int card_type) : type(static_cast<Type>(card_type)), useable(true) {

}

Card::Type Card::get_type() const{
    return type;
}

void Card::set_useable(bool k){
    this->useable = k;
}

bool Card::can_use() const{
    return useable;
}

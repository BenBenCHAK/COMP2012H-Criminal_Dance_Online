#include "Card.h"

// constructor initialize the card type and set the card can be used
Card::Card(int card_type) : type(static_cast<Type>(card_type)), selectable(true) {

}

// mutator that set whether the card can be used or not
void Card::set_selectable(bool k){
    this->selectable = k;
}

// accessors
Card::Type Card::get_type() const{
    return type;
}

bool Card::can_select() const{
    return selectable;
}

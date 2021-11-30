#include "Card.h"

Card::Card(int card_type) : type(static_cast<Type>(card_type)), useable(true) {

}

string Card::typeToAddress() const
{
    switch (type) {
        case Card::Type::ACCOMPLICE:
            return ":/resources/images/Accomplice.png";
        case Card::Type::ALIBI:
            return ":/resources/images/Alibi.png";
        case Card::Type::BARTER:
            return ":/resources/images/Barter.png";
        case Card::Type::BASTET:
            return ":/resources/images/Bastet.png";
        case Card::Type::BYSTANDER:
            return ":/resources/images/Bystander.png";
        case Card::Type::CULPRIT:
            return ":/resources/images/Culprit.png";
        case Card::Type::DETECTIVE:
            return ":/resources/images/Detective.png";
        case Card::Type::FIRST_FINDER:
            return ":/resources/images/First_Finder.png";
        case Card::Type::INFO_EXCHANGE:
            return ":/resources/images/Information_Exchange.png";
        case Card::Type::JUVENILE:
            return ":/resources/images/Juvenile.png";
        case Card::Type::RUMOR:
            return ":/resources/images/Rumor.png";
        case Card::Type::WITNESS:
            return ":/resources/images/Witness.png";
    }

    return "";
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

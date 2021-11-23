#include "InfoExchange.h"
#include "../Card.h"

Card::CardType InfoExchange::get_type() const{
    return Card::CardType::INFO_EXCHANGE;
}
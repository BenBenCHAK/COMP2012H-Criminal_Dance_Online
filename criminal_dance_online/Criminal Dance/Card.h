#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class Card {
    public:
        enum class Type{
            FIRST_FINDER = 1, 
            CULPRIT = 2, 
            DETECTIVE = 3, 
            ALIBI = 4, 
            ACCOMPLICE = 5, 
            WITNESS = 6, 
            BYSTANDER = 7, 
            BASTET = 8, 
            INFO_EXCHANGE = 9, 
            RUMOR = 10, 
            BARTER = 11, 
            JUVENILE = 12
        };
        Card(int type);
        Card::Type get_type();
        void set_useable(bool k);
        bool can_use();
    private:
        Type type;
        bool useable;
};

#endif
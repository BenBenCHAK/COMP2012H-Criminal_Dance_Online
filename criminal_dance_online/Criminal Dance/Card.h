/***********************************
/*
/*
/*
/*
/***********************************/
#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class Card {
    public:
        // different type of cards in this game
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
        // constructor that the paremeter is the card type
        Card(int type);
        // using default destructor
        ~Card() = default;
        
        // accessor
        Card::Type get_type() const;
        bool can_use() const;
        
        // mutator
        void set_useable(bool k);
    private:
        // type of this card
        Type type;
        // whether this card can exchange or not
        bool useable;
};

#endif

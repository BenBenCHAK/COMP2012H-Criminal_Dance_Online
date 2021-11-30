/***********************************
/* This class is the actual card of this game, there are 12 different type of cards in this game
/* So there are only two date members in this class, ie. const Type type represents which card type is this card from the 12 different type 
/*                                                       and bool selectable represents whether this card can be exchanged/passed/drawn or not.
/* Also, card itself will not have any operation in the game, it is just an indactor what the player wants to do, so this class only have accessors and mutator.
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
        Card(const int& type);
        // using default destructor since no new date member in Card type
        ~Card() = default;
        
        // accessors
        const Card::Type get_type() const;
        const bool can_select() const;
        
        // mutator
        void set_selectable(bool k);

        // for Qt display different type of card
        string typeToAddress() const;
    
    private:
        // type of this card ( never changes the type once this card is constructed)
        const Type type;
        // whether this card can be exchanged/passed/drawn or not
        bool selectable;
};

#endif

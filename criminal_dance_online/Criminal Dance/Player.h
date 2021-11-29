/*************************************
/*
/*
/*
/*
/************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

extern bool game_over;

class Player {
public:
    enum class Type {
        CIVILIAN = 1,
        CULPRIT = 2,
        ACCOMPLICE = 3
    };

    Player* next_player;
    Player* prev_player;
    
    // constructor 
    Player(string name);
    // destructor to deallocate the new card type in Vector<Card*> hand
    ~Player();

    void add_new_player(string name);
    
    bool is_player1();
    void reset();
    bool is_first_player();

    void init_hand(vector<int> card_list);
    
    int has_card(int type);
    int select_card();
    bool can_select_card(int index);
    int exchange_select_card();
    int draw_select_card();

    Player* select_target();
    void add_card(Card* card);

    void use_card(int index);
    // after
    void reset_useable_cards();

    // Print Messages
    void print_select_target_list(int& player_index);

    // Mutator
    void set_type(const Type& type);

    // Accessors
    string get_name() const;
    string get_hand() const;
    string get_type() const;
    // return a pointer pointing to the card which hand[index] is pointing at
    Card* get_card(const int& index) const;



private:
    // Name of a player
    string name;
    // Whether a player is the first player, ie. who distrubuted the FIRST_FINDER card.
    // This cannot make to const bool because we first create Player then distrubute the card. We don't know whether a player is the first one or not when creating a player.
    bool first_player;
    // This represent the card holding by the player (pointer to card).
    vector<Card*> hand;
    // Represent 3 different type of the player
    Type type;

};

#endif //GAMEENGINE_H

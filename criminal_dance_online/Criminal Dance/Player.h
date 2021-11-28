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
    void reset_useable_cards();

    // Print Messages
    void print_select_target_list(int& player_index);

    // Mutator
    void set_type(Type type);

    // accessors
    string get_name() const;
    string get_hand() const;
    Card* get_card(int index) const;
    string get_type() const;



private:
    vector<Card*> hand;
    string name;
    Type type;
    bool first_player;

};

#endif //GAMEENGINE_H

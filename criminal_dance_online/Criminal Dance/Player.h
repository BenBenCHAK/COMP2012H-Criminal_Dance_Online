/*************************************
/* Player are created using this class Player, this will store the player name, his/her own card in hand, his/her type, his/her next player and pervious player, 
/* and whether this player is the first player to use card.
/* Since every player knows his/her next player and pervious player, every players are linked together and the game will continous by moving the turn to next player.
/* When a player use a card, first will check whether the card can be use. If it can be use, operations will be conductd according to the type of used card.
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
    
public:
    // 3 different player type in this game 
    enum class Type {
        CIVILIAN = 1,
        CULPRIT = 2,
        ACCOMPLICE = 3
    };
    
    // Circularly linked with the next player and the previous player
    Player* next_player;
    Player* prev_player;
    
    // Constructor 
    Player(string name);
    // Destructor to deallocate the new card type in Vector<Card*> hand (Card is dynamic allocated)
    ~Player();
    
    // These function is used when initalizing the game
    void add_new_player(string name);
    void reset();
    bool is_first_player();
    void init_hand(vector<int> card_list);
    
    // Accessors
    string get_name() const;
    bool is_player1() const;
    string get_hand() const;
    string get_type() const;
    // Return a pointer pointing to the card which hand[index] is pointing at.
    Card* get_card(const int& index) const;
    
    // Mutator
    void set_type(const Type& type);
    
    // Check whether the player has the input type of card, if yes, return the position in vector hand, otherwise return -1.
    int has_card(int type);
    
    // Return the index of which card the player want to use of vector hand. Return -1 if the player does not have any cards in hand.
    int select_card();
    // Return whether the card can be used according to the card use limitation.
    bool can_select_card(int index);
    // Input the card position in vector hand and use the card, ie. do operation according to the card type.
    void use_card(int index);
    
    // Print Messages
    void print_select_target_list(int& player_index);
    // Choose a player who must have card(s) in hand
    Player* select_target();
    
    // For using INFO_EXCHANGE card type to select the pass card. Return the index of which card this wants to pass to the next player.
    // Return -1 if this player does not have any passable cards.
    int exchange_select_card();
    
    // For using RUMOR card type to select the draw card. Return the index of which card this player wants to draw from the previous player vector hand. 
    // Return -1 if previous player does not have any drawable cards.
    int draw_select_card();
    
    // Input a point to card. Add this card to this player vector hand, that card cannot be passed/drawn again in this round.
    void add_card(Card* card);
    
    // After passing/drawing/exchanging cards for a round, need to reset all card to selectable.
    void reset_AllCards_selectable();
};

#endif //GAMEENGINE_H

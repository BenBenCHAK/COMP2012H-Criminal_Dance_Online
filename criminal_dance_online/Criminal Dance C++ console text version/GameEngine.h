/*********************************
/* This is the Game Engine for operating the game.
/* Game will be constructed through this class.
/* It store the number of players in this match, and the current player and round.
/* Creating a unique random deck just for this match, and then distrubuting 4 cards to each player.
/* Providing the match infomations of the game.
/*********************************/
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Player.h"

using namespace std;

class GameEngine {
public:
    // constructor
    GameEngine();
    // destructor for deallocate the new Player type
    ~GameEngine();
    // User input functions
    const int prompt_for_num_players();
    const string prompt_for_player_name();

    // Builds game
    vector<int> set_deck();
    void distribute_cards();
    void find_first_player();

    // game run function until the end of game
    void run();

    // accessor
    const int get_number_of_players() const;
    
    // Print functions
    void print_all_player_status() const;
    
    enum class GameOption {
        CHOOSE_CARD = 1,
        QUIT = 2
    };

private:
    // number of players in this match
    const int number_of_players;
    // which player need to use card
    Player* current_player;
    // the deck in this match, will become empty after distrubuting the card to players
    vector<int> deck;
    // currently is what round 
    int round;
};

#endif //GAMEENGINE_H

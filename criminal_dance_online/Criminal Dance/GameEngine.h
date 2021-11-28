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
    GameEngine();
    // User input
    int prompt_for_num_players();
    string prompt_for_player_name();

    // Builds game
    vector<int> set_deck();
    void distribute_cards();
    void find_first_player();

    void run();

    // Print
    void print_all_players();
    void print_current_player();
    void print_all_player_status();
    
    // accessors
    int get_number_of_players() const;

    enum class GameOption {
        CHOOSE_CARD = 1,
        QUIT = 2
    };

private:
    const int number_of_players;
    Player* current_player;
    vector<int> deck;
    int round;
};

#endif //GAMEENGINE_H
/*********************************
/*
/*
/*
/*
/*********************************/
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include <QString>

#include "Player.h"

using namespace std;

class GameEngine {
public:
    // constructor
    GameEngine(QStringList name_list);
    // destructor for deallocate the new Player type
    ~GameEngine();

    // Builds game
    vector<int> set_deck();
    void distribute_cards();
    void find_first_player();

    void run();
    void nextRound();
    void prevPlayer();
    void nextPlayer();

    // Print functions
    void print_all_players();
    void print_current_player();
    void print_all_player_status();
    
    // accessors
    int get_number_of_players() const;
    Player *getCurrentPlayer();

    QString getCurrentPlayerName() {return QString::fromStdString(current_player->get_name());}
    int getCurrentPlayerNumCards() {return current_player->getHandSize();}
    Card::Type getCurrentPlayerHand(int index) {return current_player->get_card(index)->get_type();}


    enum class GameOption {
        CHOOSE_CARD = 1,
        QUIT = 2
    };

private:
    // number of players in this match
    const int number_of_players;
    // which player need to use card
    Player* current_player;
    // the deck in this match
    vector<int> deck;
    // currently is what round
    int round;
};

#endif //GAMEENGINE_H

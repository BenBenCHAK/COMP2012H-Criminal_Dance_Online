#include "GameEngine.h"

// constructor
GameEngine::GameEngine():number_of_players(prompt_for_num_players()), deck(set_deck()){
    int num_players = number_of_players;
    // Create player list   
    this->current_player = new Player(prompt_for_player_name());
    
    while (num_players>1){
        current_player->add_new_player(prompt_for_player_name());
        num_players--;
    }
    
    distribute_cards();
    // set current player pointing to player who holding FIRST_FINDER
    find_first_player();
    cout << endl;
    
    print_all_player_status();
    cout << endl << " ================ Match created ================ " << endl << endl;
    // Game ready to start.
    
}

// destructor for deallocate the new Player type
GameEngine::~GameEngine(){
    Player* p1 = current_player;
    Player* p2 = current_player->next_player;
    p1->prev_player->next_player == nullptr;
    for(int i = 0; i < number_of_players;++i){
        delete p1;
        p1 = p2;
        if(p2 != nullptr)
            p2 = p2->next_player;
    }
}

// User input function
const int GameEngine::prompt_for_num_players(){
    int num_players;
    while (true){
        cout << "How many players? (3-8)" << endl;
        cin >> num_players;

        if (num_players >2 && num_players<9){
            return num_players;
        }
        cout << "Out of bounds." << endl;
        cout << endl;
    }
}

// User input function
const string GameEngine::prompt_for_player_name(){
    string player_name;
    cout << "What is your name?" << endl;
    cin >> player_name;
    return player_name;
}

// set the deck for this game since the deck is randomly formed for each game
vector<int> GameEngine::set_deck(){
    // number represent the card type
    vector<int> all_cards = {1,2,3,4,5,4,3,5,4,4,4,3,3,6,6,6,7,7,8,9,9,9,9,10,10,10,10,10,11,11,11,11,12};
    // new_deck is the deck formed for this game
    vector<int> new_deck;
    // generate a random seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    switch(number_of_players){
        case 3: /* 3 Players: 12 cards
                   4 essential cards (first 4 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE, ALIBI] + 8 cards drawn from other 29 cards */
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+4);
            all_cards.erase(all_cards.begin(),all_cards.begin()+4);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+8);
            break;
        case 4: /* 4 Players: 16 cards
                   5 essential cards (first 5 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE, ALIBI, ACCOMPLICE] + 11 cards drawn from other 28 cards */
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+5);
            all_cards.erase(all_cards.begin(),all_cards.begin()+5);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+11);
            break;
        case 5: /* 5 Players: 20 cards
                   6 essential cards (first 6 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE, ALIBI * 2, ACCOMPLICE] + 14 cards drawn from other 27 cards */
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+6);
            all_cards.erase(all_cards.begin(),all_cards.begin()+6);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+14);
            break;
        case 6: /* 6 Players: 24 cards
                   8 essential cards (first 8 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE * 2, ALIBI * 2, ACCOMPLICE * 2] + 16 cards drawn from other 25 cards */
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+8);
            all_cards.erase(all_cards.begin(),all_cards.begin()+8);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+16);
            break;
        case 7: /* 7 Players: 28 cards
                   9 essential cards (first 9 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE * 2, ALIBI * 3, ACCOMPLICE * 2] + 19 cards drawn from other 24 cards */
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+9);
            all_cards.erase(all_cards.begin(),all_cards.begin()+9);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+19);
            break;
        case 8: /* 8 Players: 32 cards
                   9 essential cards (first 9 cards in all_deck) [FIRST_FINDER, CULPRIT, DETECTIVE * 2, ALIBI * 3, ACCOMPLICE * 2] + 23 cards drawn from other 24 cards */
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+9);
            all_cards.erase(all_cards.begin(),all_cards.begin()+9);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+23);
            break;
    }
    // randomly shuffle the new_deck
    shuffle(new_deck.begin(),new_deck.end(),std::default_random_engine(seed));
    return new_deck;
}

// distribute 4 cards to each player
void GameEngine::distribute_cards(){
    Player* temp = current_player;
    vector<int> temp_hand;
    do{
        temp_hand.insert(temp_hand.end(), deck.begin(), deck.begin()+4);
        deck.erase(deck.begin(), deck.begin()+4);
        temp->init_hand(temp_hand);
        temp_hand.clear();
        temp = temp->next_player;
    } while (!temp->is_player1());
}

// set the current player to whom is holding FIRST_FINDER as the first player to start
void GameEngine::find_first_player(){
    Player* temp = current_player->next_player;
    while (temp != current_player){
        temp->reset();
        temp = temp->next_player;
    }

    while (!current_player->is_first_player()){
        current_player = current_player->next_player;
    }
}

// game run function until the end of game
void GameEngine::run(){
    // Check whether there are player holding the JUVENILE card, if yes, let him/her knows which player is holding the CULPRIT card at the beginning
    Player* temp = current_player;
    for(int i = 0; i < number_of_players; ++i, temp = temp->next_player){
        if(temp->has_card(12) != -1){
            cout << "There are player holding JUVENILE card (He/She will know which player is holding the CULPRIT card at the beginning)." << endl;
            cout << temp->get_name() << " knows ";
            Player* temp2 = current_player;
            for(int i = 0; i < number_of_players; ++i, temp2 = temp2->next_player){
                if(temp2->has_card(2) != -1){
                    cout << temp2->get_name() << " is holding the CULPRIT card." << endl;
                }
            }
        }
    }
    
    round = 0;
    while(!game_over){
        print_all_player_status();
        cout << endl;
        
        // when a round has passed, print the current round
        if (current_player->is_player1()){
            round++;
            cout << " ================ ROUND " << round << " ================"<< endl << endl;
        }
        
        // let the current select to use which card
        cout << current_player->get_name() << ": ";
        int selected_card = current_player->select_card();
        
        // if select_card() return -1, that means current player has no card in hand, skip to next player
        if(selected_card == -1){
            cout << " You dont have any cards to use now, so you are skipped " << endl;
            current_player = current_player->next_player;
            continue;
        }
        
        // current player has card to use and perform the operations
        current_player->use_card(selected_card);
        // move to next player turn
        current_player = current_player->next_player;
    }
    
    // print the result
    print_all_player_status();
    cout << "Game Over" << endl;
    return;
}

// accessor
const int GameEngine::get_number_of_players() const{
    return number_of_players;
}

// print all the players with their corresponding type and card list
void GameEngine::print_all_player_status() const{
    Player* temp = current_player;
    cout << endl;
    for(int i = 0; i<number_of_players;++i){
        cout << "  | " << temp->get_name() << ": " << temp->get_type() << endl;
        cout << "  | " << temp->get_hand() <<  endl;
        temp = temp->next_player;
    }
}


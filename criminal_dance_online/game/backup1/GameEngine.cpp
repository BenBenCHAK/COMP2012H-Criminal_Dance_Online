#include <QString>
#include <QDebug>

#include "GameEngine.h"

GameEngine::GameEngine(QStringList name_list):number_of_players(name_list.size()), deck(set_deck()){
    int num_players = 1;
    // Create player list
    this->current_player = new Player(name_list[0].toStdString());
    while (num_players < number_of_players){
        current_player->add_new_player(name_list[num_players].toStdString());
        num_players++;
    }

    distribute_cards();
    find_first_player();

    print_all_player_status();
    // Game ready to start.

    round = 0;

    QString juvenile_message = "";
    Player* temp = current_player;
    for(int i = 0; i < number_of_players; ++i, temp = temp->next_player){
        if(temp->has_card(12) != -1){
            juvenile_message = QString::fromStdString(temp->get_name()) + QString(" knows ");

            Player* temp2 = current_player;
            for(int i = 0; i < number_of_players; ++i, temp2 = temp2->next_player){
                if(temp2->has_card(2) != -1){
                    juvenile_message += QString::fromStdString(temp2->get_name()) + QString(" is holding the CULPRIT card.");
                }
            }
        }
    }
    qDebug() << juvenile_message;
}

GameEngine::~GameEngine(){
    Player* p1 = current_player;
    Player* p2 = current_player->next_player;
    p1->prev_player->next_player = nullptr;
    for(int i = 0; i < number_of_players;++i){
        delete p1;
        p1 = p2;
        if(p2 != nullptr)
            p2 = p2->next_player;
    }
}

vector<int> GameEngine::set_deck(){
    vector<int> all_cards = {1,2,3,4,5,4,3,5,4,4,4,3,3,6,6,6,7,7,8,9,9,9,9,10,10,10,10,10,11,11,11,11,12};
    vector<int> new_deck;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    switch(number_of_players){
        case 3:
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+4);
            all_cards.erase(all_cards.begin(),all_cards.begin()+4);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+8);
            break;
        case 4:
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+5);
            all_cards.erase(all_cards.begin(),all_cards.begin()+5);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+11);
            break;
        case 5:
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+6);
            all_cards.erase(all_cards.begin(),all_cards.begin()+6);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+14);
            break;
        case 6:
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+8);
            all_cards.erase(all_cards.begin(),all_cards.begin()+8);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+16);
            break;
        case 7:
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+9);
            all_cards.erase(all_cards.begin(),all_cards.begin()+9);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+19);
            break;
        case 8:
            new_deck.insert(new_deck.begin(), all_cards.begin(), all_cards.begin()+9);
            all_cards.erase(all_cards.begin(),all_cards.begin()+9);
            shuffle(all_cards.begin(),all_cards.end(),std::default_random_engine(seed));
            new_deck.insert(new_deck.end(), all_cards.begin(), all_cards.begin()+23);
            break;
    }
    shuffle(new_deck.begin(),new_deck.end(),std::default_random_engine(seed));
    return new_deck;
}

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

void GameEngine::run(){
    round = 0;
    Player* temp = current_player;
    for(int i = 0; i < number_of_players; ++i, temp = temp->next_player){
        if(temp->has_card(12) != -1){
            cout << temp->get_name() << " knows ";

            Player* temp2 = current_player;
            for(int i = 0; i < number_of_players; ++i, temp2 = temp2->next_player){
                if(temp2->has_card(2) != -1){
                    cout << temp2->get_name() << " is holding the CULPRIT card." << endl << endl;
                }
            }
        }
    }
    while(!game_over){
        print_all_player_status();
        cout << endl;
        if (current_player->is_player1()){
            round++;
            cout << endl << "-------------ROUND " << round << endl << endl;
        }
        /*
        if (current_player->has_card(2) != -1){
            current_player->set_type(Player::Type::CULPRIT);
        }
        */
        cout << current_player->get_name() << ": ";
        int selected_card = current_player->select_card();
        if(selected_card == -1){
            cout << current_player->get_name() << " You dont have any cards to use now, so you are skipped " << endl;
            current_player = current_player->next_player;
            continue;
        }
        current_player->use_card(selected_card);
        current_player = current_player->next_player;
    }
    print_all_player_status();
    cout << "Game Over" << endl;
    return;
}

void GameEngine::nextRound()
{
    round++;
    if (round > 1) qDebug() << "Next Round!!!";
}

void GameEngine::prevPlayer()
{
    current_player = current_player->prev_player;
}
void GameEngine::nextPlayer()
{
    current_player = current_player->next_player;
}

int GameEngine::get_number_of_players() const{
    return number_of_players;
}

Player *GameEngine::getCurrentPlayer()
{
    return current_player;
}

void GameEngine::print_all_players(){
    Player* temp = current_player;
    for(int i = 0; i<number_of_players;++i){
        cout << temp->get_name() << ", " << temp->get_type() << endl;
        temp = temp->next_player;
    }
}

void GameEngine::print_current_player(){
    cout << current_player->get_name() << endl;
}

void GameEngine::print_all_player_status(){
    Player* temp = current_player;
    for(int i = 0; i<number_of_players;++i){
        cout << "  | " << temp->get_name() << ", " << temp->get_type() << endl;
        cout << "  | " << temp->get_hand() <<  endl;
        temp = temp->next_player;
    }
}


#include "Player.h"

bool game_over = false;

Player::Player(string name) : name(name), type(Player::Type::CIVILIAN), first_player(true), prev_player(this), next_player(this) {}

Player::~Player(){
    for(;hand.empty() == false;){
        delete hand[0];
        hand.erase(hand.begin());
    }
}

void Player::add_new_player(string name){ //Circularly linked
    Player* new_player = new Player(name);
    new_player->first_player = false;
    new_player->prev_player = prev_player;
    new_player->next_player = this;

    prev_player->next_player = new_player;
    prev_player = new_player;
}

bool Player::is_first_player(){
    if (has_card(1) == -1){
        first_player = false;
    } else {
        first_player = true;
    }
    return first_player;
}

bool Player::is_player1(){
    return first_player;
}

void Player::reset(){
    first_player = false;
}

void Player::init_hand(vector<int> card_list){
    for (int i = 0; i<card_list.size(); i++){
        hand.push_back(new Card(card_list[i]));
    }
}

int Player::has_card(int type){
    for (int i = 0; i < hand.size(); i++){
        if (hand[i]->get_type() == static_cast<Card::Type>(type)){
            return i;
        }
    }
    return -1;
}

int Player::exchange_select_card(){
    if(hand.size() == 0)
        return -1;
    if(hand.size() == 1 && hand[0]->can_use() == false)
        return -1;
    int selected_card;
    cout << get_name() << ": Please select a card to pass/exchange/abandon." << endl;
    cout << "Card List: " << get_hand() << endl;
    do{
        cin >> selected_card;
        selected_card--;
        if(hand[selected_card]->can_use() == false){
            cout << "This card cannot be passed again." << endl;
        }
    }while(hand[selected_card]->can_use() == false);
    return selected_card;
}

int Player::draw_select_card(){
    if(prev_player->hand.size() == 0)
        return -1;
    if(prev_player->hand.size() == 1 && prev_player->hand[0]->can_use() == false)
        return -1;
    int draw_selected_card;
    cout << get_name() << ": Please select a card you want to draw from " << prev_player->get_name() << endl;
    cout << "Card List: " << prev_player->get_hand() << endl;
    do{
        cin >> draw_selected_card;
        draw_selected_card--;
        if(prev_player->hand[draw_selected_card]->can_use() == false){
            cout << "This card cannot be drawn again." << endl << endl;
        }
    }while(prev_player->hand[draw_selected_card]->can_use() == false);
    return draw_selected_card; 
}

int Player::select_card(){
    if(hand.size() == 0)
        return -1;
    int selected_card;
    cout << "Please select a card to use." << endl;
    cout << "Card List: " << get_hand() << endl;
    cin >> selected_card;
    selected_card--;

    while (!can_select_card(selected_card)){
        cout << endl << "Cannot select this card. Please select another." << endl << endl;
        cout << "Please select a card to use." << endl;
        cout << "Card List: " << get_hand() << endl;
        cin >> selected_card;
        selected_card--;
    }

    return selected_card;
}

Player* Player::select_target(){
    Player* target = this;
    int player_index;
    int target_index;
    while(true){
        target = this;
        print_select_target_list(player_index);
        cin >> target_index;
        while (target_index<0 || target_index>player_index){
            cout << "Out of Bounds." << endl;
            print_select_target_list(player_index);
            cin >> target_index;
        }

        for (int i=0; i<target_index; i++){
            target = target->next_player;
        }
        if(target->hand.size() > 0) // if the target has no cards repeat to choose target again 
            break;
        cout << "You can't choose players with no cards." << endl << endl;
    }
    cout << endl;
    return target;
}

void Player::add_card(Card* card){
    card->set_useable(false);
    hand.push_back(card);
}

void Player::reset_useable_cards(){
    Player* temp = this;
    do{
        for(int i = 0; i < temp->hand.size(); ++i){
            temp->hand[i]->set_useable(true);
        }
        temp = temp->next_player;
    }while (temp != this);
}

void Player::print_select_target_list(int& player_index){
    Player* temp = this->next_player;
    player_index = 1;
    cout << "Choose a player to target: " << endl;
    while (temp != this){
        cout << player_index << ". " << temp->get_name() << endl;
        temp = temp->next_player;
        player_index++;
    }
}

void Player::use_card(int index){
    Player* target;
    Card* removing_card = hand[index];
    int card_type = static_cast<int>(removing_card->get_type());

    // i think delete the card in hand first is better to prevent exchanging the used card
    if(static_cast<int>(removing_card->get_type())!=8){
        delete removing_card;
        hand.erase(hand.begin()+index);
    }

    switch (card_type){
        case 1:
            break;

        case 2:{
            set_type(Player::Type::CULPRIT);
            game_over = true;
            cout << "The CULPRIT used his/her last card" << endl;
            cout << "CULPRIT and ACCOMPLICE wins" << endl;
            Player* temp = this;
            do{
                if(temp->type != Player::Type::CIVILIAN){
                    cout << temp->get_name() << " wins " << endl;
                }
                else{
                    cout << temp->get_name() << " lose " << endl;
                }
                temp = temp->next_player;
            }while(temp != this);
            
            break;
        }
        case 3:{
            if(hand.size() == 3) // no effect when player use at first turn (3 since if use as the 4th card hand only have 3 cards)
                break;
            target = select_target();
            if (target->has_card(4) != -1 || target->has_card(2) == -1){
                cout << target->get_name() << " is not the culprit." << endl;
                target->set_type(Player::Type::CIVILIAN);
            } 
            else {
                target->set_type(Player::Type::CULPRIT);
                cout << "The DETECTIVE found the CULPRIT." << endl;
                cout << "CIVILIAN wins" << endl;
                Player* temp = this;
                game_over = true;
                do{
                    if(temp->type == Player::Type::CIVILIAN){
                        cout << temp->get_name() << " wins " << endl;
                    }
                    else{
                        cout << temp->get_name() << " lose " << endl;
                    }
                    temp = temp->next_player;
                }while(temp != this);
            }
            break;
        }
        case 4:
            break;

        case 5:
            set_type(Player::Type::ACCOMPLICE);
            break;

        case 6:
            target = select_target();
            cout << endl;
            cout << target->get_name() << "'s hands: ";
            cout << target->get_hand() << endl << endl;
            break;

        case 7:
            break;

        case 8:{
            reset_useable_cards();
            target = select_target();
            int abandon_card_index = target->exchange_select_card();
            // CULPRIT abandon the CULPRIT card
            if(abandon_card_index == target->has_card(2)){
                target->set_type(Player::Type::CULPRIT);
                cout << "The BASTET made the CULPRIT abandon the CULPRIT card." << endl;
                cout << "CIVILIAN wins" << endl;
                game_over = true;
                Player* temp = this;
                do{
                    if(temp->type == Player::Type::CIVILIAN){
                        cout << temp->get_name() << " wins " << endl;
                    }
                    else{
                        cout << temp->get_name() << " lose " << endl;
                    }
                    temp = temp->next_player;
                }while(temp != this);
                break;
            }
            // otherwise
            delete target->hand[abandon_card_index];
            target->hand.erase(target->hand.begin()+abandon_card_index);
            target->add_card(removing_card);
            hand.erase(hand.begin()+index);

            reset_useable_cards();
            break;
        }
        case 9: {// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> all players will join passing card even they have no cards in hand
            reset_useable_cards();
            Player* current = this;
            do{
                cout << endl;
                int passing_card_index = current->exchange_select_card();
                if(passing_card_index == -1){
                    cout << endl;
                    cout << "You ( " << current->get_name() << " ) don't have any passable cards." << endl;
                    current = current->next_player;
                    continue;
                }

                target = current->next_player;

                target->add_card(current->get_card(passing_card_index));
                current->hand.erase(current->hand.begin()+passing_card_index);
                current = current->next_player;
            }while (current != this);

            reset_useable_cards();
            break;
        }
        case 10:{// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> all players will join drawing card even they have no cards in hand
            reset_useable_cards();
            Player* current = this;
            do{
                cout << endl;
                int draw_card_index = current->draw_select_card();
                if(draw_card_index == -1){
                    cout << endl;
                    cout << current->prev_player->get_name() << " doesn't have any passable cards to let you ( " << current->get_name() << " ) draw." << endl;
                    current = current->next_player;
                    continue;
                }
                target = current->prev_player;
                current->add_card(target->get_card(draw_card_index));
                target->hand.erase(target->hand.begin()+draw_card_index);
                current = current->next_player;
            }while (current != this);

            reset_useable_cards();
            break;
        }
        case 11:{// >>>>>>>>if user dont have card in hand, this user take a card from other player instead of exchange the cards
            reset_useable_cards();
            Player* current = this;
            target = select_target();
            cout << endl;
            int current_give_card_index = current->exchange_select_card();
            cout << endl;
            int target_give_card_index = target->exchange_select_card();

            if(current_give_card_index == -1){ // take card from target only
                current->add_card(target->get_card(target_give_card_index));
                target->hand.erase(target->hand.begin()+target_give_card_index);
            }

            else{ // exchange card
                current->add_card(target->get_card(target_give_card_index));
                target->add_card(current->get_card(current_give_card_index));
                current->hand.erase(current->hand.begin()+current_give_card_index);
                target->hand.erase(target->hand.begin()+target_give_card_index);
            }

            reset_useable_cards();
            break;
        }  
        case 12:
            break;
    }
}

void Player::set_type(Player::Type type){
    this->type = type;
}

// only for use card select but not the passing/exchanging/drawing/abandoning
bool Player::can_select_card(int index){
    if (index>=hand.size()||index<0){
        return false;
    }
    switch (static_cast<int>(hand[index]->get_type())){
        case 1: 
            return true;
        case 2: // cant use CULPRIT unless it is the less card
            if (hand.size()!=1){
                return false;
            }
            break;

        case 3: // DETECTIVE cant be use when having 4 cards unless holding 1 CULPRIT and 3 DETECTIVE or 4 DETECTIVE
            if (hand.size() == 4){
                for(int i = 0; i < hand.size(); ++i){
                    if (static_cast<int>(hand[i]->get_type()) != 3 && static_cast<int>(hand[i]->get_type()) != 2)
                        return false;
                }
            }
            break;

        default: // force first finder to use first finder
            if(has_card(1) != -1)
                return false;
            break;
    }
    return true;
}

string Player::get_name() const{
    return name;
}

string Player::get_type() const{
    switch(type){
        case Player::Type::CIVILIAN:
            return "Civilian";
        case Player::Type::CULPRIT:
            return "Culprit";
        case Player::Type::ACCOMPLICE:
            return "Accomplice";
    }
    return "";
}

string Player::get_hand() const{
    string card_list = "[ ";
    
    for (int i = 0; i<hand.size(); i++){
        switch(static_cast<int>(hand[i]->get_type())){
            case 1:{
                card_list += "FIRST_FINDER  ";
                break;
            }
            case 2:{
                card_list += "CULPRIT  ";
                break;
            }
            case 3:{
                card_list += "DETECTIVE  ";
                break;
            }
            case 4:{
                card_list += "ALIBI  ";
                break;
            }
            case 5:{
                card_list += "ACCOMPLICE  ";
                break;
            }
            case 6:{
                card_list += "WITNESS  ";
                break;
            }
            case 7:{
                card_list += "BYSTANDER  ";
                break;
            }
            case 8:{
                card_list += "BASTET  ";
                break;
            }
            case 9:{
                card_list += "INFO_EXCHANGE  ";
                break;
            }
            case 10:{
                card_list += "RUMOR  ";
                break;
            }
            case 11:{
                card_list += "BARTER  ";
                break;
            }
            case 12:{
                card_list += "JUVENILE  ";
                break;
            }
        }
    }
    
    card_list += "]";
    return card_list;
}

Card* Player::get_card(int index) const{
    return hand[index];
}

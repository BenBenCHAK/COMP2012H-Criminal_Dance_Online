#include "Player.h"

bool game_over = false;

// Constructor 
Player::Player(const string& name) : name(name), type(Player::Type::CIVILIAN), first_player(true), prev_player(this), next_player(this) {}

// Destructor to deallocate the new card type in Vector<Card*> hand (Card is dynamic allocated)
Player::~Player(){
    for(;hand.empty() == false;){
        delete hand[0];
        hand.erase(hand.begin());
    }
}

// Add and link the player
void Player::add_new_player(const string& name){
    Player* new_player = new Player(name);
    new_player->first_player = false;
    new_player->prev_player = prev_player;
    new_player->next_player = this;

    prev_player->next_player = new_player;
    prev_player = new_player;
}

void Player::reset(){
    first_player = false;
}

// Initialize which player is the first player
const bool Player::is_first_player(){
    if (has_card(1) == -1){
        first_player = false;
    } else {
        first_player = true;
    }
    return first_player;
}

// Distribute cards
void Player::init_hand(vector<int> card_list){
    for (int i = 0; i<card_list.size(); i++){
        hand.push_back(new Card(card_list[i]));
    }
}

// Accessors
const string Player::get_name() const{
    return name;
}

const bool Player::is_player1() const{
    return first_player;
}

// Get the hand card list
const string Player::get_hand() const{
    string card_list = "[ ";
    
    for (int i = 0; i<hand.size(); i++){
        switch(static_cast<int>(hand[i]->get_type())){
            case 1:{
                card_list += "FIRST_FINDER ";
                break;
            }
            case 2:{
                card_list += "CULPRIT ";
                break;
            }
            case 3:{
                card_list += "DETECTIVE ";
                break;
            }
            case 4:{
                card_list += "ALIBI ";
                break;
            }
            case 5:{
                card_list += "ACCOMPLICE ";
                break;
            }
            case 6:{
                card_list += "WITNESS ";
                break;
            }
            case 7:{
                card_list += "BYSTANDER ";
                break;
            }
            case 8:{
                card_list += "BASTET ";
                break;
            }
            case 9:{
                card_list += "INFO_EXCHANGE ";
                break;
            }
            case 10:{
                card_list += "RUMOR ";
                break;
            }
            case 11:{
                card_list += "BARTER ";
                break;
            }
            case 12:{
                card_list += "JUVENILE ";
                break;
            }
        }
    }
    
    card_list += "]";
    return card_list;
}

const string Player::get_type() const{
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

Card* Player::get_card(const int& index) const{
    return hand[index];
}

void Player::set_type(const Player::Type& type){
    this->type = type;
}

// Check whether the player has the input type of card, if yes, return the position in vector hand, otherwise return -1.
const int Player::has_card(const int& type) const{
    for (int i = 0; i < hand.size(); i++){
        if (hand[i]->get_type() == static_cast<Card::Type>(type)){
            return i;
        }
    }
    return -1;
}

// Return the index of which card the player want to use of vector hand. Return -1 if the player does not have any cards in hand.
const int Player::select_card() const{
    if(hand.size() == 0)
        return -1;
    int selected_card;
    cout << "Please select a card to use." << endl;
    cout << "Card List: " << get_hand() << endl;
    cin >> selected_card;
    selected_card--;
    
    // repect to force player to select a useable card
    while (!can_select_card(selected_card)){
        cout << endl << "Cannot select this card. Please select another." << endl << endl;
        cout << "Please select a card to use." << endl;
        cout << "Card List: " << get_hand() << endl;
        cin >> selected_card;
        selected_card--;
    }

    return selected_card;
}

// Return whether the card can be used according to the card usage limitation.
const bool Player::can_select_card(const int& index) const{
    // out of bound
    if (index>=hand.size()||index<0){
        return false;
    }
    
    switch (static_cast<int>(hand[index]->get_type())){
        case 1: // always can use FIRST_FINDER
            return true;
        case 2: // cant use CULPRIT unless it is the last card
            if (hand.size()!=1){
                return false;
            }
            break;

        case 3: // DETECTIVE cant be use when having 4 cards unless holding [CULPRIT + DETECTIVE * 3] or [DETECTIVE * 4] , but it will do nothings
            if (hand.size() == 4){
                for(int i = 0; i < hand.size(); ++i){
                    if (static_cast<int>(hand[i]->get_type()) != 3 && static_cast<int>(hand[i]->get_type()) != 2) // That means the player has other type of card
                        return false;
                }
            }
            break;

        default: // Force first player to use FIRST_FINDER
            if(has_card(1) != -1) // That means the player has FIRST_FINDER card
                return false;
            break;
    }
    return true;
}

// Input the card position in vector hand and use the card, ie. do operation according to the card type.
void Player::use_card(const int& index){
    Player* target;
    Card* removing_card = hand[index];
    int card_type = static_cast<int>(removing_card->get_type());

    // Because BASTET card will always exist on the game, so it will not be deleted when used
    if(static_cast<int>(removing_card->get_type())!=8){
        delete removing_card;
        hand.erase(hand.begin()+index);
    }

    switch (card_type){
        case 1: // FIRST_FINDER -> do nothings
            return;

        case 2:{ // CULPRIT -> Criminals wins and print out the result
            set_type(Player::Type::CULPRIT);
            game_over = true;
            cout << "The CULPRIT used his/her last card" << endl;
            cout << "CULPRIT and ACCOMPLICE wins" << endl << endl;
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
            
            return;
        }
        case 3:{ // DETECTIVE -> accuse a player holding CULPRIT card
            if(hand.size() == 3) // do nothings when player use at the first turn (4 holding cards).
                return;
            
            target = select_target();
            // the targeted player is not holding the CULPRIT card or having ALIBI at the same time
            if (target->has_card(4) != -1 || target->has_card(2) == -1){
                cout << target->get_name() << " is not the culprit." << endl;
            } 
            // sucessfully guess who is holding CULPRIT card -> CIVILIAN wins and print out the result
            else { 
                target->set_type(Player::Type::CULPRIT);
                cout << "The DETECTIVE found the CULPRIT." << endl;
                cout << "CIVILIAN wins" << endl << endl;
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
            return;
        }
        case 4: // ALIBI -> do nothing
            return;

        case 5: // ACCOMPLICE -> set player type to ACCOMPLICE
            set_type(Player::Type::ACCOMPLICE);
            return;

        case 6: // WITNESS -> choose a player to view his/her all card in hand.
            target = select_target();
            cout << endl;
            cout << target->get_name() << "'s hands: ";
            cout << target->get_hand() << endl << endl;
            return;

        case 7: // BYSTANDER -> do nothings
            return;

        case 8:{ // BASTET -> Choose a player who need to discard a card from his/her hand.
            reset_AllCards_selectable();
            target = select_target();
            int abandon_card_index = target->exchange_select_card();
            
            // targered player discard the CULPRIT card -> CIVILIAN wins and print out the result
            if(abandon_card_index == target->has_card(2)){
                target->set_type(Player::Type::CULPRIT);
                
                delete target->hand[abandon_card_index];
                target->hand.erase(target->hand.begin()+abandon_card_index);
                delete removing_card;
                hand.erase(hand.begin()+index);
                
                cout << "The BASTET made the CULPRIT abandon the CULPRIT card." << endl;
                cout << "CIVILIAN wins" << endl << endl;
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
                return;
            }
            
            // targered player discard the other card -> targeted player receive this card (BASTET) to his/her hand 
            delete target->hand[abandon_card_index];
            target->hand.erase(target->hand.begin()+abandon_card_index);
            target->add_card(removing_card);
            hand.erase(hand.begin()+index);

            reset_AllCards_selectable();
            return;
        }
        case 9: { /* INFO_EXCHANGE -> Starting from this player, choose a card in hand and pass to the next player and repect this process one by one. 
                     Players can see the recived card but cannot pass the recived card again to the next player. 
                     If current player does not have any passable card, ie. no cards in hand or the only card is the recived card,
                     then skip the current player (next player will not receive any card but still need to proced the above process). */
            
            // reset all card to selectable(passable)
            reset_AllCards_selectable();
            Player* current = this;
            
            // repect the process for a round.
            do{
                cout << endl;
                int passing_card_index = current->exchange_select_card();
                
                // this player does not have any passable card to pass, so skip to the next player 
                if(passing_card_index == -1){
                    cout << endl;
                    cout << "You ( " << current->get_name() << " ) don't have any passable cards to pass to " << current->next_player->get_name() << " ." << endl;
                    current = current->next_player;
                    continue;
                }

                target = current->next_player;
                
                // add the passed card to the next player and remove from the current player
                target->add_card(current->get_card(passing_card_index));
                current->hand.erase(current->hand.begin()+passing_card_index);
                
                current = current->next_player;
            }while (current != this);
            
            // operations done, reset all card to selectable
            reset_AllCards_selectable();
            return;
        }
        case 10:{ /* RUMOR -> Starting from this player, draw a card from the pervious player and repect this process one by one.
                     The card drawn from the pervious player cannot be drawn again by the next player. 
                     If the pervious player does not have any drawable card to let the current player draw, ie. no cards in hand or the only card is the drawn card, 
                     then skip the current player (current player will not draw and receive any cards but still need to proced the above process). */
            
            // reset all card to selectable (drawable)
            reset_AllCards_selectable();
            Player* current = this;
            
            // repect the process for a round.
            do{
                cout << endl;
                int draw_card_index = current->draw_select_card();
                
                // the previous player does not have any drawable card to let current player draw, so skip the current player to next player.
                if(draw_card_index == -1){
                    cout << endl;
                    cout << current->prev_player->get_name() << " doesn't have any drawable cards to let you ( " << current->get_name() << " ) draw." << endl;
                    current = current->next_player;
                    continue;
                }
                
                target = current->prev_player;
                
                // add the drawn card to the current player and remove from the previous player
                current->add_card(target->get_card(draw_card_index));
                target->hand.erase(target->hand.begin()+draw_card_index);
                
                current = current->next_player;
            }while (current != this);

            // operations done, reset all card to selectable
            reset_AllCards_selectable();
            return;
        }
        case 11:{ /* BARTER -> choose a player who have card in hand to exchange a card. 
                     If current player does not have any cards in hand, he/she will take the card from the targeted player instead of exchanging. */
            
            // reset all card to selectable
            reset_AllCards_selectable();
            Player* current = this;
            target = select_target();
            cout << endl;
            int current_give_card_index = current->exchange_select_card();
            cout << endl;
            int target_give_card_index = target->exchange_select_card();
            
            // current player does not have any cards in hand, take the card from the targeted player
            if(current_give_card_index == -1){
                // add the taken card to the current player and remove from the targeted player
                current->add_card(target->get_card(target_give_card_index));
                target->hand.erase(target->hand.begin()+target_give_card_index);
            }
            
            // exchange card
            else{
                // add the received card to the current player and add the given card to the targeted player
                current->add_card(target->get_card(target_give_card_index));
                target->add_card(current->get_card(current_give_card_index));
                // remove the received card from the targeted player and remove the given card from the current player
                current->hand.erase(current->hand.begin()+current_give_card_index);
                target->hand.erase(target->hand.begin()+target_give_card_index);
            }
            
            // reset all card to selectable
            reset_AllCards_selectable();
            return;
        }  
        case 12: // JUVENILE -> do nothings
            return;
    }
}

// used for print target player selection
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

// Choose a player who must have card(s) in hand
Player* Player::select_target(){
    Player* target = this;
    int player_index;
    int target_index;
    
    while(true){
        target = this;
        print_select_target_list(player_index);
        cin >> target_index;
        
        // out of bound input
        while (target_index<0 || target_index>player_index){
            cout << "Out of Bounds." << endl;
            print_select_target_list(player_index);
            cin >> target_index;
        }

        for (int i=0; i<target_index; i++){
            target = target->next_player;
        }
        
        // leave the loop only when the targeted player have card in hand
        if(target->hand.size() > 0) 
            break;
        cout << "You can't choose players with no cards." << endl << endl;
    }
    
    cout << endl;
    return target;
}

// For using INFO_EXCHANGE, BARTER and BASTET card type to select the passing/exchanging/discarding card.
// Return the index of which card this player wants to choose. Return -1 if this player does not have any passable/exchangeble cards.
const int Player::exchange_select_card()const{
    // Return -1 if this player does not have any passable/exchangeble cards. (For BASTET card type, it will never return -1 since the targeted player must have card(s) in hand.)
    if(hand.size() == 0)
        return -1;
    if(hand.size() == 1 && hand[0]->can_select() == false)
        return -1;
    
    int selected_card;
    cout << get_name() << ": Please select a card to pass/exchange/discard." << endl;
    cout << "Card List: " << get_hand() << endl;
    
    do{
        cin >> selected_card;
        selected_card--;
        
        // For INFO_EXCHANGE card only, since BARTER and BASTET card will always selectable
        // the received card cannot be passed again
        if(hand[selected_card]->can_select() == false){
            cout << "This card cannot be passed again." << endl;
        }
        
    }while(hand[selected_card]->can_select() == false);
    
    return selected_card;
}

// For using RUMOR card type to select the drawn card. Return the index of which card this player wants to draw from the previous player vector hand. 
// Return -1 if previous player does not have any drawable cards.
const int Player::draw_select_card()const{
    // Return -1 if previous player does not have any drawable cards.
    if(prev_player->hand.size() == 0)
        return -1;
    if(prev_player->hand.size() == 1 && prev_player->hand[0]->can_select() == false)
        return -1;
    
    int draw_selected_card;
    cout << get_name() << ": Please select a card you want to draw from " << prev_player->get_name() << endl;
    cout << "Card List: " << prev_player->get_hand() << endl;
    
    do{
        cin >> draw_selected_card;
        draw_selected_card--;
        
        // the drawn card cannot be drawn again
        if(prev_player->hand[draw_selected_card]->can_select() == false){
            cout << "This card cannot be drawn again." << endl << endl;
        }
        
    }while(prev_player->hand[draw_selected_card]->can_select() == false);
    
    return draw_selected_card; 
}

// Input a point to card. Add this card to this player vector hand, that card cannot be passed/drawn again in this round.
void Player::add_card(Card* const card){
    card->set_selectable(false);
    hand.push_back(card);
}

// After passing/drawing/exchanging/discarding cards for a round, reset all cards to selectable.
void Player::reset_AllCards_selectable(){
    Player* temp = this;
    do{
        for(int i = 0; i < temp->hand.size(); ++i){
            temp->hand[i]->set_selectable(true);
        }
        temp = temp->next_player;
    }while (temp != this);
}

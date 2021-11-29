Criminal Dance
********************************************
Criminal Dance is a faction game, in which CULPRIT need to hide his/her identity and Civilians need to try their best to find who is holding CULPRIT. However, since the identity of players will be exchanged, which increase the uncertainty and interest. 
********************************************
Number of Player:
  3-8

Gaming time:
  5-10 mins

Game direction:
  Circular clockwise, Player will use card one by one and do the operation accounding to the used card. 
  If a player does not have any cards in hand, skip this player and continous to next player.
  
Number of cards:
  Every match in this game has different card deck. It is consist of the essential cards and randomly picked cards accounding to the number of players.
  
  In total there are 33 cards.
  [ FIRST_FINDER * 1,
    CULPRIT * 1, 
    DETECTIVE * 4, 
    ALIBI * 5, 
    ACCOMPLICE * 2, 
    WITNESS * 3, 
    BYSTANDER * 2, 
    BASTET * 1, 
    INFO_EXCHANGE * 4, 
    RUMOR * 5, 
    BARTER * 4, 
    JUVENILE * 1 ]

  3 Players: 12 cards
    4 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE , ALIBI ] + 8 cards drawn from other 29 cards 
  4 Players: 16 cards
    5 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE , ALIBI , ACCOMPLICE ] + 11 cards drawn from other 28 cards 
  5 Players: 20 cards
    6 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE , ALIBI * 2 , ACCOMPLICE ] + 14 cards drawn from other 27 cards 
  6 Players: 24 cards
    8 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE * 2 , ALIBI * 2 , ACCOMPLICE * 2 ] + 16 cards drawn from other 25 cards 
  7 Players: 28 cards
    9 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE * 2 , ALIBI * 3 , ACCOMPLICE * 2 ] + 19 cards drawn from other 24 cards 
  8 Players: 32 cards
    9 essential cards [ FIRST_FINDER , CULPRIT , DETECTIVE * 2 , ALIBI * 3 , ACCOMPLICE * 2 ] + 23 cards drawn from other 24 cards
    
  Each player will randomly distributed 4 cards from the above deck.
  
Game faction:
  Criminals ( CULPRIT, ACCOMPLICE)
  Civilians (other players)
  
Card function:
  FIRST_FINDER:   This card indicat who is the first player to start the match. This player must use this card and no actions are done.
  
  CULPRIT:        This card can be used only if it is the last card left in hand. Once it is used, Criminals wins and Civilian loses.
  
  DETECTIVE:      Player can only use this card when he/she is holding 3 or less cards in hand (in case of the player must use this card, ie. holding CULPRIT + DETECTIVE * 3,
                  this card can be used with no actions are done.) Civilians wins and Criminals loses if the player can catch which player is holding the CULPRIT card.
                  
  ALIBI:          This card do no actions when used. If a player is holding the CULPRIT card and this card at the same time, he/she will not be catched by DETECTIVE.
  
  ACCOMPLICE:     The player who use this card in his/her turn will become an accomplice (not effected when just holding in hand). Sharing the same match outcome with culprit.
  
  WITNESS:        Choose a player to view his/her all card in hand.
  
  BYSTANDER:      This card do no actions when used.
  
  BASTET:         Choose a player who need to discard a card from his/her hand. If the discarded card is CULPRIT, Civilian wins and Criminals loses. Otherwise, the target player                   receive this card to his/her hand.
  
  INFO_EXCHANGE:  Starting from the player who use this card, choose a card in hand and pass to left side player and repect this process clockwise direction one by one. 
                  The Player can see the recived card but cannot pass the recived card again to the next player. 
                  If a player does not have any passable card, ie. no cards in hand or the only card is the recived card, then skip this player. 
                  
  RUMOR:          Starting from the player who use this card, draw a card from the right side player and repect this process in clockwise direction one by one. 
                  The card drawn from right side player cannot be drawn again from the left side player. 
                  If a player does not have any drawable card to let the left side player draw, ie. no cards in hand or the only card is the drawn card, 
                  then skip the left side playe. 
                  
  BARTER:         Player who use this card can choose a player who have card in hand to exchange a card in hand. 
                  If the player does not have any card in hand, he/she will take the card from the target player instead of exchanging. 
                  
  JUVENILE:       At the begining of the match, player who have this card can know which player is holding the CULPRIT card at first. This card do no actions when used.
  
========================================================================================================================================================================

C++ Console Text version
********************************************
How to use the program
Creating Players list
adding each next player means that the player added is sitting at previous player left hand side in the real world
Example:
3
a
b
c

a's next player is b; b's next player is c; c's next player is a
a left hand side is b; b left hand side is c; c left hand side is a


using card by entering int [ 1 , num of card]

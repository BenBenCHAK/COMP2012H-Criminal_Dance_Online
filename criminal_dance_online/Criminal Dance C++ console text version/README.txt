Criminal Dance (犯人在跳舞)
********************************************
Criminal Dance is a faction game. In the game, CULPRIT need to hide his/her identity and Civilians need to try their best to find who is holding CULPRIT. 
However, since the identity of players will be exchanged, which increase the uncertainty and interest. 
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
  FIRST_FINDER:   This card indicate who is the first player to start the match. This player must use this card and no actions are done.
  
  CULPRIT:        This card can be used only if it is the last card left in hand. Once it is used, Criminals wins and Civilian loses.
  
  DETECTIVE:      Player can only use this card when he/she is holding 3 or less cards in hand (in case of the player must use this card, ie. holding CULPRIT + DETECTIVE * 3,
                  this card can be used with no actions are done.) Civilians wins and Criminals loses if the player can catch which player is holding the CULPRIT card.
                  
  ALIBI:          This card do no actions when used. If a player is holding the CULPRIT card and this card at the same time, he/she will not be catched by DETECTIVE.
  
  ACCOMPLICE:     The player who use this card in his/her turn will become an accomplice (not effected when just holding in hand). 
                  Sharing the same match outcome with culprit.
  
  WITNESS:        Choose a player to view his/her all card in hand.
  
  BYSTANDER:      This card do no actions when used.
  
  BASTET:         Choose a player who need to discard a card from his/her hand. If the discarded card is CULPRIT, Civilian wins and Criminals loses. 
                  Otherwise, the targeted player receive this card to his/her hand.
  
  INFO_EXCHANGE:  Starting from this player, choose a card in hand and pass to the next player and repect this process one by one. 
                  Players can see the recived card but cannot pass the recived card again to the next player. 
                  If current player does not have any passable card, ie. no cards in hand or the only card is the recived card,
                  then skip the current player (next player will not receive any card but still need to proced the above process).
                  
  RUMOR:          Starting from this player, draw a card from the pervious player and repect this process one by one.
                  The card drawn from the pervious player cannot be drawn again by the next player. 
                  If the pervious player does not have any drawable card to let the current player draw, ie. no cards in hand or the only card is the drawn card, 
                  then skip the current player (current player will not draw and receive any cards but still need to proced the above process). 
                  
  BARTER:         Player who use this card can choose a player who have card in hand to exchange a card in hand. 
                  If the player does not have any card in hand, he/she will take the card from the targeted player instead of exchanging. 
                  
  JUVENILE:       At the begining of the match, player who have this card can know which player is holding the CULPRIT card at first. This card do no actions when used.
  
=================================================================================================================================================================================
C++ Console Text version program
********************************************
  Important Notes
********************************************
In this C++ Console Text version program every player holding card are shown as it is the only way to conduct a multiplayer board game in a sereen.
So every status of each player are shown at each turn. 
Even when player are drawing card, it still show the actual card of the player. Which is just for C++ Console Text version program.
or Even guessing which player is holding the Culprit card.
Also, Player type will not change each turn to who holding the CULPRIT card since the identiy is changing. 
Player type will only be changed when using card that will change identity permanently, ie, [CULPRIT, ACCOMPLICE] and when CULPRIT get catched.
********************************************
How to use the program:
  step 1: Enter the number of players of the match.
  step 2: Enter the player's name one by one.
  step 3: Player can play the game by enter their choose. And the game goes on until finished.
  
Player creating order:
  For example in the player naming section:
      a
      b
      c
  is entered.
  
  a's next player is b; b's next player is c; c's next player is a
  a left hand side is b; b left hand side is c; c left hand side is a
  The game conducted in circular clockwise direction, ie. a->b->c->a/ b->c->a->b / c->a->b->c.
  
  Here is an actual creating the match:
      How many players? (3-8)
      3
      What is your name?
      a
      What is your name?
      b
      What is your name?
      c


        | c: Civilian
        | [  FIRST_FINDER  RUMOR  DETECTIVE  BASTET  ]
        | a: Civilian
        | [  BARTER  ALIBI  INFO_EXCHANGE  ACCOMPLICE  ]
        | b: Civilian
        | [  CULPRIT  WITNESS  RUMOR  JUVENILE  ]

       ================ Match created ================

      There are player holding JUVENILE card (He/She will know which player is holding the CULPRIT card at the beginning).
      b knows b is holding the CULPRIT card.

        | c: Civilian
        | [  FIRST_FINDER  RUMOR  DETECTIVE  BASTET  ]
        | a: Civilian
        | [  BARTER  ALIBI  INFO_EXCHANGE  ACCOMPLICE  ]
        | b: Civilian
        | [  CULPRIT  WITNESS  RUMOR  JUVENILE  ]

       ================ ROUND 1 ================

      c: Please select a card to use.
      Card List: [  FIRST_FINDER  RUMOR  DETECTIVE  BASTET  ]


Crad selection:
  Select card by entering integer in [ 1 , num of card]
  
  Example:
      a: Please select a card to use.
      Card List: [ RUMOR  DETECTIVE  FIRST_FINDER  INFO_EXCHANGE  ]
      
  Player a need to select a card by entering integer 1/2/3/4.
  
 Target selection:
  Select target player by entering the provided corresponding integer number of the player.
  
  Example:
      Choose a player to target: 
      1. c
      2. a
      
   player b need to enter 1 to target player c or 2 to target player a.
   
   
 End of the game:
  When a game is finished each player will be printed with the result and the player type and current holding cards.
  There are 3 ways to finish a game and the result will be printed as follow:
  
    1) DETECTIVE sucessfully find the CULPRIT card           - Civilians wins & Criminals loses 
        
            c: Please select a card to use.
            Card List: [  DETECTIVE  BASTET  ALIBI  ]
            1

            Choose a player to target:
            1. a
            2. b
            2

            The DETECTIVE found the CULPRIT.
            CIVILIAN wins

            c wins
            a wins
            b lose

              | a: Civilian
              | [  INFO_EXCHANGE  ACCOMPLICE  RUMOR  ]
              | b: Culprit
              | [  CULPRIT  WITNESS  RUMOR  ]
              | c: Civilian
              | [  BASTET  ALIBI  ]

             ================ Game Over ================

    2) CULPRIT used as the last card                         - Civilians loses & Criminals wins 
    
            c: Please select a card to use.
            Card List: [  CULPRIT  ]
            1

            The CULPRIT used his/her last card
            CULPRIT and ACCOMPLICE wins

            c wins
            a wins
            b lose

              | a: Accomplice
              | [  INFO_EXCHANGE  ]
              | b: Civilian
              | [  ALIBI  ]
              | c: Culprit
              | [  ]

             ================ Game Over ================
    
    3) BASTET force targeted player discard the CULPRIT card - Civilians wins & Criminals loses 
    
            a: Please select a card to use.
            Card List: [  WITNESS  BASTET  DETECTIVE  ALIBI  ]
            2

            Choose a player to target:
            1. b
            2. c
            1

            b: Please select a card to pass to c / exchange / discard.
            Card List: [  INFO_EXCHANGE  RUMOR  CULPRIT  ALIBI  ]
            3

            The BASTET made the targeted player discard the CULPRIT card.
            CIVILIAN wins

            a wins
            b lose
            c wins

              | b: Culprit
              | [  INFO_EXCHANGE  RUMOR  ALIBI  ]
              | c: Civilian
              | [  INFO_EXCHANGE  DETECTIVE  ACCOMPLICE  ]
              | a: Civilian
              | [  WITNESS  DETECTIVE  ALIBI  ]

             ================ Game Over ================
  

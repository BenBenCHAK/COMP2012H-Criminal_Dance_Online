Criminal Dance Instructions

The program isn't finished, I haven't worked on setting unexchangeable cards, finding the winner etc.
It currently can start the game, set players and card decks
Iterate through players and make them use cards (use index of the card list instead of card type)
Ends the game when 
1. Detective finds the culprit
2. Bastet finds the culprit
3. Culprit uses their last card
(Cannot leave in middle of the game yet)

Targeting players work (Witness, Bastet, detective)

Eg. If card list = [ 3 5 6 2 ]
Can't use 2(Culprit) and 3(detective, only on the first turn!)
Use 5 by inputting 2


// Completed
FIRST_FINDER = 1, 
CULPRIT = 2, 
DETECTIVE = 3, 
ALIBI = 4, 
ACCOMPLICE = 5, 
WITNESS = 6, 
BYSTANDER = 7, 
BASTET = 8, 

//WIP
INFO_EXCHANGE = 9, 
RUMOR = 10, 
BARTER = 11, 
JUVENILE = 12, 
CONSTABULARY = 13
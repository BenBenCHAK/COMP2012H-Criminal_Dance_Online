#ifndef CARD_H
#define CARD_H
class Card{
public:
    enum class CardType{
        FIRST_FINDER = 1, 
        CULPRIT = 2, 
        DETECTIVE = 3, 
        BASTET = 4, 
        RUMOR = 5, 
        ALIBI = 6, 
        INFO_EXCHANGE = 7, 
        WITNESS = 8, 
        BARTER = 9, 
        BYSTANDER = 10, 
        ACCOMPLICE = 11, 
        JUVENILE = 12, 
        CONSTABULARY = 13
    };

    virtual Card::CardType get_type() const = 0;
    virtual bool use() const;

    // Culprit
    virtual bool check_culprit() const;
};

#endif
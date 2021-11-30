#include "visualplayer.h"
#include <QDebug>
#include <QBrush>
#include <QFont>

VisualPlayer::VisualPlayer()
{
    setAcceptHoverEvents(true);
}

void VisualPlayer::setCircle(QGraphicsEllipseItem *circle, bool is_turn, QGraphicsTextItem *name)
{
    this->circle = circle;

    this->is_in_turn = is_turn;

    this->circle->setBrush(is_turn ? QBrush(QColor(255, 0, 255)) : QBrush(QColor(255, 0, 255, 100)));

    addToGroup(this->circle);

    this->name = name;
    this->name->setDefaultTextColor(Qt::black);
    this->name->setFont(QFont("Comic Sans MS", 20));

    addToGroup(this->name);
}

void VisualPlayer::setPlayerIndex(int i)
{
    player_index = i;
}
void VisualPlayer::setName(QString name)
{
    player_name = name;
}
void VisualPlayer::setNumCard(int cards)
{
    cards_left = cards;
}

void VisualPlayer::setNumCardChange(int change)
{
    cards_left += change;
}
void VisualPlayer::setIsAccomplice(bool k)
{
    is_accomplice = k;
}
void VisualPlayer::setIsInTurn(bool k)
{
    is_in_turn = k;
    this->circle->setBrush(k ? QBrush(QColor(255, 0, 255)) : QBrush(QColor(255, 0, 255, 100)));
}

int VisualPlayer::getPlayerIndex()
{
    return player_index;
}
QString VisualPlayer::getName()
{
    return player_name;
}
int VisualPlayer::getNumCard()
{
    return cards_left;
}
bool VisualPlayer::getIsAccomplice()
{
    return is_accomplice;
}

void VisualPlayer::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit entered(player_name, cards_left, is_accomplice);
    if (!is_in_turn) this->circle->setBrush(QBrush(QColor(255, 0, 255, 150))); else this->circle->setBrush(QBrush(QColor(255, 0, 255, 255)));
    QGraphicsItemGroup::hoverEnterEvent(event);
}
void VisualPlayer::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!is_in_turn) this->circle->setBrush(QBrush(QColor(255, 0, 255, 100))); else this->circle->setBrush(QBrush(QColor(255, 0, 255, 255)));
    QGraphicsItemGroup::hoverLeaveEvent(event);
}

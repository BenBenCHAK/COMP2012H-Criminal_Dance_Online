#include "visualcard.h"

#define CARD_WIDTH 407
#define CARD_HEIGHT 570

#include <QPixmap>

VisualCard::VisualCard()
{
    isPressed = false;
    isMouseInside = false;

    card_width = CARD_WIDTH * 0.5;
    card_height = CARD_HEIGHT * 0.5;

    setAcceptHoverEvents(true);

    setTransformOriginPoint(card_width / 2, card_height * 0.9);
    setTransformationMode(Qt::SmoothTransformation);
}

int VisualCard::getWidth()
{
    return card_width;
}
int VisualCard::getHeight()
{
    return card_height;
}

void VisualCard::setCard(Card *card, int card_index)
{
    this->card = card;
    this->card_index = card_index;
}

void VisualCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    isPressed = true;

    emit clicked(card, card_index);

    QGraphicsItem::mousePressEvent(event);
}

void VisualCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isPressed = false;

    emit released();

    QGraphicsItem::mouseReleaseEvent(event);
}
void VisualCard::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    isMouseInside = true;

    setScale(1.75);
    setZValue(1);

    QGraphicsItem::hoverEnterEvent(event);
}
void VisualCard::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    isMouseInside = false;

    setScale(1);
    setZValue(0);

    QGraphicsItem::hoverLeaveEvent(event);
}

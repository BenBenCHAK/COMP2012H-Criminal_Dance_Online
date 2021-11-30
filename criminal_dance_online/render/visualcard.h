#ifndef VISUALCARD_H
#define VISUALCARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include <QDebug>
#include "game/Card.h"

class VisualCard : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    VisualCard();

    int getWidth();
    int getHeight();

    void setCard(Card *card, int card_index);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void clicked(Card *card, int card_index);
    void released();

private:
    bool isPressed;
    bool isMouseInside;

    int card_width;
    int card_height;

    Card *card;
    int card_index;
};

#endif // VISUALCARD_H

#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "game/GameEngine.h"

#include "visualcard.h"
#include "visualplayer.h"

class Render : public QGraphicsView
{
    Q_OBJECT
public:
    struct PlayerSection
    {
        QGraphicsRectItem *section;
        QGraphicsTextItem *name;
        QGraphicsTextItem *num_cards;
        QGraphicsTextItem *accomplice_state;
        int center_x;
        int center_y;
        int side;
        QString player_name;
        int num_cards_left;
        bool is_accomplice;
    };

    explicit Render(QStringList name_list);

    void showView();

public slots:
    void displayDetails(QString player_name, int num_cards_left, bool is_accomplice);
    void handles(Card *card, int index);
    void nextTurn();

    void printDebugMessage();

signals:

private:
    GameEngine *game;

    QGraphicsView *view;
    QGraphicsScene *scene;

    PlayerSection player_section;
    QGraphicsPixmapItem *discard_zone;

    VisualPlayer *players;
    VisualCard *cards;
};

#endif // RENDER_H

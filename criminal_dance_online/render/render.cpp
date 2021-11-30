#include "render.h"

#include <QObject>
#include <QString>
#include <QtMath>
#include <QDebug>

#define WIDTH 1440
#define HEIGHT 900

Render::Render(QStringList name_list)
{
    game = new GameEngine(name_list);

    view = new QGraphicsView();
    scene = new QGraphicsScene(0, 0, WIDTH, HEIGHT);

    view->setFixedSize(WIDTH, HEIGHT);

    scene->setBackgroundBrush(QPixmap(":/resources/images/background_3.png"));

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view->setScene(scene);

    // Initialize player section
    player_section.side = HEIGHT * 0.225;
    player_section.center_x = WIDTH * 0.15 + player_section.side / 2;
    player_section.center_y = HEIGHT * 0.2 + player_section.side / 2;

    player_section.section = new QGraphicsRectItem(WIDTH * 0.15, HEIGHT * 0.2, player_section.side, player_section.side);
    player_section.section->setPen(QPen(Qt::black, 10));
    player_section.section->setBrush(QBrush(QColor(0, 0, 0, 100)));

    player_section.name = new QGraphicsTextItem();
    player_section.num_cards = new QGraphicsTextItem();
    player_section.accomplice_state = new QGraphicsTextItem();

    player_section.name->setDefaultTextColor(Qt::white);
    player_section.num_cards->setDefaultTextColor(Qt::white);
    player_section.accomplice_state->setDefaultTextColor(Qt::white);

    player_section.name->setFont(QFont("Comic Sans MS", 20));
    player_section.num_cards->setFont(QFont("Comic Sans MS", 20));
    player_section.accomplice_state->setFont(QFont("Comic Sans MS", 20));

    player_section.name->setPos(player_section.center_x - player_section.side / 2, player_section.center_y - player_section.side / 2);
    player_section.num_cards->setPos(player_section.center_x - player_section.side / 2, player_section.center_y - player_section.side / 2 + player_section.side / 3);
    player_section.accomplice_state->setPos(player_section.center_x - player_section.side / 2, player_section.center_y - player_section.side / 2 + player_section.side / 3 * 2);

    scene->addItem(player_section.section);
    scene->addItem(player_section.name);
    scene->addItem(player_section.num_cards);
    scene->addItem(player_section.accomplice_state);

    // Initialize players
    int num_players = game->get_number_of_players();
    players = new VisualPlayer [num_players];
    Player *temp_player = game->getCurrentPlayer();

    for (int i = 0; i < num_players; i++) {
        int radius = 50, dist = player_section.side;

        QPoint coords(player_section.center_x + dist * qCos(2 * M_PI / num_players * i + M_PI_2) - radius, player_section.center_y + dist * qSin(2 * M_PI / num_players * i + M_PI_2) - radius);

        QGraphicsEllipseItem *temp_circle = new QGraphicsEllipseItem(coords.x(), coords.y(), radius * 2, radius * 2);
        QGraphicsTextItem *temp_name = new QGraphicsTextItem(QString::fromStdString(temp_player->get_name()).left(3));
        temp_name->setPos(coords.x() + radius - temp_name->boundingRect().width(), coords.y() + radius - temp_name->boundingRect().height());

        players[i].setCircle(temp_circle, i == 0, temp_name);
        players[i].setPlayerIndex(i);
        players[i].setName(QString::fromStdString(temp_player->get_name()));
        players[i].setNumCard(temp_player->getHandSize());
        players[i].setIsAccomplice(temp_player->getType() == Player::Type::ACCOMPLICE);
        players[i].setIsInTurn(temp_player == game->getCurrentPlayer());
        scene->addItem(&players[i]);

        temp_player = temp_player->next_player;
    }

    // Initialize cards
    int numCards = game->getCurrentPlayerNumCards();

    cards = new VisualCard [numCards];
    for (int i = 0; i < numCards; i++) {
        cards[i].setCard(game->getCurrentPlayer()->get_card(i), i);
        cards[i].setPixmap(QPixmap(QString::fromStdString(game->getCurrentPlayer()->get_card(i)->typeToAddress())).scaled(cards[i].getWidth(), cards[i].getHeight()));
        cards[i].setPos(WIDTH / (numCards + 1) * (i + 1) - cards[i].getWidth() / 2, HEIGHT - cards[i].getHeight() - HEIGHT * 0.05);
        scene->addItem(&cards[i]);
    }

    // Discard zone
    discard_zone = new QGraphicsPixmapItem();
    discard_zone->setPos(WIDTH / 2, HEIGHT * 0.05);
    discard_zone->setScale(0.85);
    scene->addItem(discard_zone);

    // Connect
    for (int i = 0; i < num_players; i++) {
        connect(&players[i], &VisualPlayer::entered, this, &Render::displayDetails);
    }
    for (int i = 0; i < numCards; i++) {
        connect(&cards[i], &VisualCard::clicked, this, &Render::handles);
        //connect(&cards[i], &VisualCard::clicked, this, &Render::nextTurn);
    }
}

void Render::showView() {
    view->show();
}

void Render::displayDetails(QString player_name, int num_cards_left, bool is_accomplice)
{
    player_section.name->setPlainText(player_name);
    player_section.num_cards->setPlainText(QString::number(num_cards_left) + QString(" card%1 left").arg(num_cards_left < 2 ? "" : "s"));
    player_section.accomplice_state->setPlainText(is_accomplice ? "Accomplice" : "");
}
void Render::handles(Card *card, int index)
{
    if (game->getCurrentPlayer()->can_select_card(index)) {
        // Find player index corresponding to card index
        int playerIndex = 0;
        Player *temp = game->getCurrentPlayer();
        while (!temp->is_first_player()) {
            playerIndex++;
            temp = temp->prev_player;
        }

        players[playerIndex].setNumCardChange(-1);
        players[playerIndex].setIsInTurn(false);
        players[(playerIndex + 1) % game->get_number_of_players()].setIsInTurn(true);
        displayDetails(players[(playerIndex + 1) % game->get_number_of_players()].getName(), players[(playerIndex + 1) % game->get_number_of_players()].getNumCard(), players[(playerIndex + 1) % game->get_number_of_players()].getIsAccomplice());

        if (game->getCurrentPlayer()->is_player1()) game->nextRound();

        discard_zone->setPixmap(QString::fromStdString(card->typeToAddress()));

        game->getCurrentPlayer()->use_card(index);

        game->nextPlayer();

        nextTurn();
        if (game_over) {
            qDebug() << "GAME OVER!!!";
            view->close();
        }


    }
}
void Render::nextTurn()
{
    /*for (int i = 0; i < 4; i++) {
        if (&cards[i] != nullptr) {
            scene->removeItem(&cards[i]);
        }
    }*/
    //if (cards != nullptr) delete [] cards;

    int numCards = game->getCurrentPlayerNumCards();
    cards = new VisualCard [numCards];
    for (int i = 0; i < numCards; i++) {
        cards[i].setPixmap(QPixmap(QString::fromStdString(game->getCurrentPlayer()->get_card(i)->typeToAddress())).scaled(cards[i].getWidth(), cards[i].getHeight()));
        cards[i].setPos(WIDTH / (numCards + 1) * (i + 1) - cards[i].getWidth() / 2, HEIGHT - cards[i].getHeight() - HEIGHT * 0.05);
        scene->addItem(&cards[i]);
    }
}

void Render::printDebugMessage() {
    qDebug() << "hiiiiiiii";
}


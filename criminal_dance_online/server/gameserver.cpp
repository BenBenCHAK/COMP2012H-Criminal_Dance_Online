#include "gameserver.h"
#include "gameserverinterface.h"
#include <algorithm>

#include <QNetworkInterface>
#include <QMessageBox>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

/*
 *  GameServerInterface::GameServerInterface(QObject *parent)
 *  @funct:  constructor for the GameServerInterface class
 *  @param:  parent: MainWindow
 *  @return: N/A
 */
GameServer::GameServer(QObject *parent):
    QTcpServer(parent)
{
    if (!listen()) {
        qDebug("Unable to start the server");
        close();
        return;
    }
    port = serverPort();

    // Find a usable IP address
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ip = ipAddressesList.at(i).toString();
            break;
        }
    }

    if (ip.isEmpty())
        ip = QHostAddress(QHostAddress::LocalHost).toString();
}

/*
 *  GameServer::get[...]
 *  @funct:  getter functions for the GameServer object
 */
QString GameServer::getIP() const {return ip;}
quint16 GameServer::getPort() const {return port;}
QVector<GameServerInterface*> GameServer::getClients() const {return clients;}

/*
 *  void GameServer::incomingConnection(qintptr socketDesriptor)
 *  @funct:  handler for when there is a new incoming client
 *  @param:  socketDesriptor: the client that is connecting to the GameServer
 *  @return: N/A
 */
void GameServer::incomingConnection(qintptr socketDesriptor) {
    qDebug("New Player");
    GameServerInterface *worker = new GameServerInterface(this);
    if (!worker->setSocketDescriptor(socketDesriptor)) {
        worker->deleteLater();
        return;
    }

    // If the room has already full, no new player is accepted
    if (clients.size() >= 5) {
        QJsonObject playerFullMsg;
        playerFullMsg["type"] = "playerFull";
        sendJson(worker, playerFullMsg);
        connect(worker, &GameServerInterface::disconnectedFromClient, this, std::bind(&GameServer::userDisconnected, this, worker));
        qDebug() << fullList;
        return;
    }

    // Send the players list to the new player
    if (!clients.isEmpty()) {
        qDebug("Send player list");
        QJsonObject playerNamesMsg;
        QJsonArray playerNames;
        for (GameServerInterface *worker : clients)
            playerNames.append(worker->getPlayerName());
        playerNamesMsg["type"] = "playerList";
        playerNamesMsg["playerNames"] = playerNames;
        sendJson(worker, playerNamesMsg);
    }

    connect(worker, &GameServerInterface::disconnectedFromClient, this, std::bind(&GameServer::userDisconnected, this, worker));
    connect(worker, &GameServerInterface::jsonReceived, this, std::bind(&GameServer::jsonReceived, this, worker, std::placeholders::_1));
    clients.append(worker);
}

/*
 *  void GameServer::jsonReceived(GameServerInterface *sender, const QJsonObject &json)
 *  @funct:  handler for when the server recieves a QJsonObject from a client
 *  @param:  sender: the client who sent the QJsonObject, json: the QJsonObject recieved
 *  @return: N/A
 */
void GameServer::jsonReceived(GameServerInterface *sender, const QJsonObject &json) {
    Q_ASSERT(sender);

    qDebug("Server Receive a Client Json");
    const QString type = json.value(QString("type")).toString();
    if (type == "playerName") {
        const QString playerName = json.value("playerName").toString();

        // If the player has the same name with existing player, server won't allow the player to enter the room
        for (GameServerInterface *worker : clients) {
            if (worker == sender)
                continue;
            if (worker->getPlayerName() == playerName) {
                QJsonObject playerRepeatNameMsg;
                playerRepeatNameMsg["type"] = "nameRepeat";
                sendJson(sender, playerRepeatNameMsg);
                fullList.append(sender);
                clients.removeAll(sender);
                return;
            }
        }

        sender->setPlayerName(playerName);
        QJsonObject newPlayerMsg;
        newPlayerMsg["type"] = "newPlayer";
        newPlayerMsg["playerName"] = playerName;
        broadcast(newPlayerMsg);
    }

    emit receiveJson(sender, json);
}

/*
 *  void GameServer::startGameBroadcast()
 *  @funct:  function to tell the clients that the game has been started by the host
 *  @param:  N/A
 *  @return: N/A
 */
void GameServer::startGameBroadcast() {
    if (clients.size()>5){
        QMessageBox::information(nullptr, QString("Too Many Players"), QString("There are too many players."));
        return;
    }
    if (clients.size()==1){
        QMessageBox::information(nullptr, QString("Not Enough Players"), QString("You need 2-5 players to play."));
        return;
    }
    qDebug("Server Start Game Broadcast");
    QJsonObject startGameMsg;
    startGameMsg["type"] = "startGame";
    broadcast(startGameMsg);
}

/*
 *  void GameServer::userDisconnected(GameServerInterface *sender)
 *  @funct:  handler for when a client disconnects
 *  @param:  worker: client that has disconnected
 *  @return: N/A
 */
void GameServer::userDisconnected(GameServerInterface *sender) {
    qDebug("user disconnect");
    if (std::find(clients.begin(), clients.end(), sender) == clients.end()) {
        fullList.removeAll(sender);
        return;
    }
    clients.removeAll(sender);
    const QString player = sender->getPlayerName();
    if (!player.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = QString("playerDisconnected");
        disconnectedMessage["playerName"] = player;
        broadcast(disconnectedMessage, nullptr);
    }
    sender->deleteLater();
}

/*
 *  void GameServer::sendJson(GameServerInterface *worker, const QJsonObject &json)
 *  @funct:  function for sending a QJsonObject from the server to the client
 *  @param:  worker: client to be sent to, json: QJsonObject to be sent
 *  @return: N/A
 */
void GameServer::sendJson(GameServerInterface *worker, const QJsonObject &json) {
    Q_ASSERT(worker);
    worker->sendJson(json);
}

/*
 *  void GameServer::broadcast(const QJsonObject &json, GameServerInterface *exclude)
 *  @funct:  function for sending a QJsonObject from the server to all the client
 *  @param:  json: QJsonObject to be sent, exclude: optional argument for a client to be not recieve the broadcast
 *  @return: N/A
 */
void GameServer::broadcast(const QJsonObject &json, GameServerInterface *exclude) {
    qDebug("Broadcast Message");
    for (GameServerInterface *worker : clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, json);
    }
}

/*
 *  void GameServer::stopServer()
 *  @funct:  function for stopping the server
 *  @param:  N/A
 *  @return: N/A
 */
void GameServer::stopServer() {
    for (GameServerInterface *worker : clients)
        worker->disconnectFromClient();
    close();
}

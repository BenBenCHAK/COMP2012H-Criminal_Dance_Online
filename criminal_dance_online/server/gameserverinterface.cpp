#include "gameserverinterface.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

/*
 *  GameServerInterface::GameServerInterface(QObject *parent)
 *  @funct:  constructor for the GameServerInterface object
 *  @param:  parent: Server
 *  @return: N/A
 */
GameServerInterface::GameServerInterface(QObject *parent):
    QObject(parent),
    serverSocket(new QTcpSocket(this))
{
    qDebug("New GameServerInterface");
    connect(serverSocket, &QTcpSocket::readyRead, this, &GameServerInterface::receiveJson);
    connect(serverSocket, &QTcpSocket::disconnected, this, &GameServerInterface::disconnectFromClient);
}

/*
 *  GameServerInterface::set[...]()
 *  @funct:  setter functions for GameServerInterface
 */
bool GameServerInterface::setSocketDescriptor(qintptr socketDescriptor) {
    return serverSocket->setSocketDescriptor(socketDescriptor);
}
void GameServerInterface::setPlayerName(const QString &playerName) {
    this->playerName = playerName;
}


/*
 *  QString GameServerInterface::getPlayerName()
 *  @funct:  returns the name of the player/client
 *  @param:  N/A
 *  @return: N/A
 */
QString GameServerInterface::getPlayerName() const {
    return playerName;
}

/*
 *  void GameServerInterface::disconnectFromClient()
 *  @funct:  signal triggered when disconnected from client
 *  @param:  N/A
 *  @return: N/A
 */
void GameServerInterface::disconnectFromClient() {
    serverSocket->disconnectFromHost();
    emit disconnectedFromClient();
}

/*
 *  void GameServerInterface::receiveJson()
 *  @funct:  triggerd when recieving a Json object
 *  @param:  N/A
 *  @return: N/A
 */
void GameServerInterface::receiveJson() {
    qDebug("GameServerInterface receive Json");
    QByteArray jsonData;
    QDataStream socketStream(serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_11);
    while(true) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    emit jsonReceived(jsonDoc.object());
                else
                    qDebug("Invalid message");
            } else {
                qDebug("Invalid message");
            }
        } else {
            break;
        }
    }
}

/*
 *  void GameServerInterface::sendJson(const QJsonObject &json)
 *  @funct:  for sending Json objects
 *  @param:  json: the Json object to be sent
 *  @return: N/A
 */
void GameServerInterface::sendJson(const QJsonObject &json) {
    QDataStream socketStream(serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_11);
    socketStream << QJsonDocument(json).toJson(QJsonDocument::Compact);
}

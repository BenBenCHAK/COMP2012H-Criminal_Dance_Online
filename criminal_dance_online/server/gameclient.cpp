#include "gameclient.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>

/*
 *  GameClient::GameClient(QObject *parent)
 *  @funct:  constructor for the GameClient object
 *  @param:  parent: MainWindow
 *  @return: N/A
 */
GameClient::GameClient(QObject *parent):
    QObject(parent),
    clientSocket(new QTcpSocket(this))
{
    connect(clientSocket, &QTcpSocket::connected, this, &GameClient::connected);
    connect(clientSocket, &QTcpSocket::disconnected, this, &GameClient::disconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &GameClient::onReadyRead);
}

/*
 *  void GameClient::connectToServer(const QHostAddress &address, quint16 port)
 *  @funct:  connects the client to the server
 *  @param:  address: adderss of the server, port: port of the server
 *  @return: N/A
 */
void GameClient::connectToServer(const QHostAddress &address, quint16 port) {
    clientSocket->connectToHost(address, port);
}

/*
 *  void GameClient::disconnectFromHost()
 *  @funct:  disconnect the client from the host
 *  @param:  N/A
 *  @return: N/A
 */
void GameClient::disconnectFromHost() {
    qDebug("client Disconnect");
    clientSocket->disconnectFromHost();
}

/*
 *  void GameClient::sendJson(const QJsonObject &json)
 *  @funct:  sends the Json from the client to the server
 *  @param:  json: QJsonObject to be sent
 *  @return: N/A
 */
void GameClient::sendJson(const QJsonObject &json) {
    QDataStream clientStream(clientSocket);
    clientStream.setVersion(QDataStream::Qt_5_11);
    clientStream << QJsonDocument(json).toJson(QJsonDocument::Compact);
}

/*
 *  void GameClient::jsonReceived(const QJsonObject &json)
 *  @funct:  slot triggered when Json object has been recieved
 *  @param:  json: QJsonObject recieved
 *  @return: N/A
 */
void GameClient::jsonReceived(const QJsonObject &json) {
    emit receiveJson(json);
}

/*
 *  void GameClient::onReadyRead()
 *  @funct:  for receiving the Json object from the server
 *  @param:  N/A
 *  @return: N/A
 */
void GameClient::onReadyRead() {
    qDebug("Client ready read");
    QByteArray jsonData;
    QDataStream socketStream(clientSocket);
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

#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>

#include <QTcpServer>
#include <QVector>

#include "gameserverinterface.h"

class GameServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(GameServer)
public:
    explicit GameServer(QObject *parent = nullptr);
    QString getIP() const;
    quint16 getPort() const;
    QVector<GameServerInterface*> getClients() const;

protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void receiveJson(GameServerInterface *sender, const QJsonObject &json);
public slots:
    void stopServer();
    void startGameBroadcast();
    void broadcast(const QJsonObject &json, GameServerInterface *exclude = nullptr);
private slots:
    void jsonReceived(GameServerInterface *sender, const QJsonObject &json);
    void userDisconnected(GameServerInterface *sender);
private:

    quint16 port;
    QString ip;
    QVector<GameServerInterface*> clients;
    QVector<GameServerInterface*> fullList;
    void sendJson(GameServerInterface *worker, const QJsonObject &json);
};

#endif // GAMESERVER_H

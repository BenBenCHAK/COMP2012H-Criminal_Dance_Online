#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QTcpSocket>
class QHostAddress;
class QJsonDocument;
class GameClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GameClient)
public:
    explicit GameClient(QObject *parent = nullptr);
    void sendJson(const QJsonObject &json);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void disconnected();
    void receiveJson(const QJsonObject &json);
private:
    QTcpSocket *clientSocket;
    void jsonReceived(const QJsonObject &doc);
};

#endif // GAMECLIENT_H

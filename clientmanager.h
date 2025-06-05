#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class ClientManager : public QObject
{
    Q_OBJECT

public:
    static ClientManager& instance()
    {
        static ClientManager instance;
        return instance;
    }

    void connectToServer(const QString& host, quint16 port)
    {
        if (!socket) {
            socket = new QTcpSocket(this);
            connect(socket, &QTcpSocket::readyRead, this, &ClientManager::onReadyRead);
            connect(socket, &QTcpSocket::connected, this, []() {
                qDebug() << "Connected to server.";
            });
            connect(socket, &QTcpSocket::disconnected, this, []() {
                qDebug() << "Disconnected from server.";
            });
        }

        socket->connectToHost(host, port);
    }

    void sendMessage(const QString& message)
    {
        if (socket && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(message.toUtf8());
        }
    }

signals:
    void messageReceived(const QString& message);

private slots:
    void onReadyRead()
    {
        QByteArray data = socket->readAll();
        emit messageReceived(QString::fromUtf8(data));
    }

private:
    ClientManager() {}
    ~ClientManager() { if (socket) socket->deleteLater(); }

    QTcpSocket* socket = nullptr;

    Q_DISABLE_COPY(ClientManager)
};

#endif // CLIENTMANAGER_H


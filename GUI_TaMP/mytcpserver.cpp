#include "mytcpserver.h"
#include <QDebug>
#include <QStringList>
#include "rsa_encryption.h"
#include "simplehash.h"
#include "bisection_method.h"
#include "graph.h"
#include <iostream>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server not started";
    } else {
        qDebug() << "Server started";
    }
}

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}



void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

    mTcpSocket->write("Connected to server. Send commands!\r\n");
}

void MyTcpServer::slotServerRead()
{
    while (mTcpSocket->bytesAvailable() > 0) {
        QByteArray array = mTcpSocket->readAll();
        buffer.append(QString::fromUtf8(array));
    }

    if (buffer.endsWith("\n") || buffer.endsWith("\r\n")) {
        QString command = buffer.trimmed();
        buffer.clear();
        QStringList parts = command.split(" ");
        QString response = "Unknown command\n";

        if (parts[0].toLower() == "login" && parts.size() == 3) {
            QString username = parts[1];
            QString password = parts[2];
            bool success = DatabaseManager::instance().checkLogin(username, password);
            response = success ? "Login successful\n" : "Login failed\n";

        } else if (parts[0].toLower() == "register" && parts.size() == 3) {
            QString username = parts[1];
            QString password = parts[2];
            bool success = DatabaseManager::instance().registerUser(username, password);
            response = success ? "Registration successful\n" : "Registration failed\n";

        } else if (parts[0].toLower() == "rsa" && parts.size() == 2) {
            int message = parts[1].toInt();
            int e = 7, n = 33; // можешь сделать эти значения параметрами
            int result = RsaEncryption::encrypt(message, e, n);
            response = QString("RSA encrypted: %1\n").arg(result);

        } else if (parts[0].toLower() == "hash" && parts.size() >= 2) {
            parts.removeFirst();
            QString input = parts.join(" ");
            unsigned long long hash = SimpleHash::hash(input.toUtf8().constData());
            response = QString("Hash: %1\n").arg(hash);

        } else if (parts[0].toLower() == "bisection" && parts.size() == 3) {
            double a = parts[1].toDouble();
            double b = parts[2].toDouble();
            double root = BisectionMethod::findRoot(a, b);
            response = QString("Root: %1\n").arg(root);

        } else if (parts[0].toLower() == "graph") {
            Graph g(5);
            g.addEdge(0, 1, 10);
            g.addEdge(0, 2, 5);
            g.addEdge(1, 2, 2);
            g.addEdge(2, 3, 3);
            g.addEdge(3, 4, 1);

            // Создаем буфер для хранения строки результата
            char result[1024]; // Можно увеличить размер буфера, если нужно
            g.dijkstraString(0, result, sizeof(result)); // Получаем строку с результатами

            // Преобразуем результат в QString для отправки
            response = QString::fromUtf8(result);
        }

        mTcpSocket->write(response.toUtf8());
    }
}


void MyTcpServer::slotClientDisconnected()
{
    mTcpSocket->close();
}


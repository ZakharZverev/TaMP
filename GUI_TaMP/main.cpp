#include <QCoreApplication>
#include <QApplication>
#include <iostream>
#include "rsa_encryption.h"
#include "simplehash.h"
#include "bisection_method.h"
#include "graph.h"
#include "mytcpserver.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    qDebug() << "Приложение запущено!";
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    // RSA шифрование
    int e = 7, d = 23, n = 33;
    int message = 5;
    int encrypted = RsaEncryption::encrypt(message, e, n);
    int decrypted = RsaEncryption::decrypt(encrypted, d, n);
    std::cout << "Encrypted: " << encrypted << ", Decrypted: " << decrypted << std::endl;

    // Хэширование
    const char* text = "Test string for hashing!";
    unsigned long long hashValue = SimpleHash::hash(text);
    std::cout << "Hash: " << hashValue << std::endl;

    // Метод деления пополам
    double root = BisectionMethod::findRoot(1, 2);
    std::cout << "Root: " << root << std::endl;

    // Алгоритм Дейкстры
    Graph graph(5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 1);
    graph.dijkstra(0);

    // Запуск сервера
    MyTcpServer server;

    // Запуск GUI клиента
    MainWindow w;
    w.show();

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "clientmanager.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), socket(new QTcpSocket(this)) {
    // Подключение к серверу
    socket->connectToHost("127.0.0.1", 33333);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readResponse);

    // Элементы интерфейса
    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    inputEdit = new QLineEdit;
    outputEdit = new QTextEdit;
    outputEdit->setReadOnly(true);

    QPushButton *loginButton = new QPushButton("Login");
    QPushButton *registerButton = new QPushButton("Register");
    QPushButton *rsaButton = new QPushButton("RSA");
    QPushButton *hashButton = new QPushButton("Hash");
    QPushButton *bisectionButton = new QPushButton("Bisection");
    QPushButton *graphButton = new QPushButton("Graph");

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::sendLogin);
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::sendRegister);
    connect(rsaButton, &QPushButton::clicked, this, &MainWindow::sendRSA);
    connect(hashButton, &QPushButton::clicked, this, &MainWindow::sendHash);
    connect(bisectionButton, &QPushButton::clicked, this, &MainWindow::sendBisection);
    connect(graphButton, &QPushButton::clicked, this, &MainWindow::sendGraph);

    // Layout
    QWidget *central = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(new QLabel("Username:"));
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(new QLabel("Password / Input:"));
    mainLayout->addWidget(passwordEdit);
    mainLayout->addWidget(new QLabel("Extra Input:"));
    mainLayout->addWidget(inputEdit);

    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(registerButton);
    mainLayout->addWidget(rsaButton);
    mainLayout->addWidget(hashButton);
    mainLayout->addWidget(bisectionButton);
    mainLayout->addWidget(graphButton);
    mainLayout->addWidget(new QLabel("Server Response:"));
    mainLayout->addWidget(outputEdit);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    ClientManager::instance().connectToServer("127.0.0.1", 1234);

    connect(&ClientManager::instance(), &ClientManager::messageReceived, this, [](const QString& msg) {
        qDebug() << "Server replied:" << msg;
    });

    // отправка сообщений
    ClientManager::instance().sendMessage("LOGIN:admin:1234");
}

MainWindow::~MainWindow() {}

void MainWindow::sendLogin() {
    QString command = "login " + usernameEdit->text() + " " + passwordEdit->text();
    socket->write(command.toUtf8() + "\n");
}

void MainWindow::sendRegister() {
    QString command = "register " + usernameEdit->text() + " " + passwordEdit->text();
    socket->write(command.toUtf8() + "\n");
}

void MainWindow::sendRSA() {
    QString command = "rsa " + inputEdit->text();
    socket->write(command.toUtf8() + "\n");
}

void MainWindow::sendHash() {
    QString command = "hash " + inputEdit->text();
    socket->write(command.toUtf8() + "\n");
}

void MainWindow::sendBisection() {
    QStringList inputs = inputEdit->text().split(" ");
    if (inputs.size() == 2) {
        QString command = "bisection " + inputs[0] + " " + inputs[1];
        socket->write(command.toUtf8() + "\n");
    } else {
        outputEdit->append("Provide two numbers for bisection.");
    }
}

void MainWindow::sendGraph() {
    socket->write("graph\n");
}

void MainWindow::readResponse() {
    QByteArray data = socket->readAll();
    outputEdit->append(QString::fromUtf8(data));
}

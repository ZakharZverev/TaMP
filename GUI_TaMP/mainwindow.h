#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTcpSocket>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendLogin();
    void sendRegister();
    void sendRSA();
    void sendHash();
    void sendBisection();
    void sendGraph();
    void readResponse();

private:
    QTcpSocket *socket;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *inputEdit;
    QTextEdit *outputEdit;
};

#endif // MAINWINDOW_H


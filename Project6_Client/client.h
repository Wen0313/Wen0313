#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void readData();

    void displayError(QAbstractSocket::SocketError socketError);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void deleteLater();

private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket = nullptr;
};

#endif // CLIENT_H

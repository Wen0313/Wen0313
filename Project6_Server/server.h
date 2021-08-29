#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtCore>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QString>
#include <QHostAddress>
#include <QDebug>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    void connectionSlot();

    void readData();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void deleteLater();

private:
    Ui::Server *ui;
    void  initServer();

    QTcpServer* tcpServer;
    QTcpSocket* tcpClient;
};

#endif // SERVER_H

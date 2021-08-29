#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    ui->pushButton->setEnabled(false);
    ui->textEdit->setReadOnly(true);
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this,
                &Client::displayError);
}

Client::~Client()
{
    delete ui;
    tcpSocket->disconnectFromHost();
}

void Client::readData()
{
    QString msg = "from Server: " + tcpSocket->readAll();
    ui->textEdit->append(msg);
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::critical(
            this, tr("Error"),
            tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
    }
}

void Client::on_pushButton_2_clicked()
{
    QString data = ui->lineEdit_2->text();
    quint16 port = quint16(data.toUInt());
    QString ip = ui->lineEdit_3->text();
    tcpSocket->connectToHost(ip,port);
    if(tcpSocket->waitForConnected(1000)){
        ui->textEdit->setText("连接成功");
    }
    else return;
    tcpSocket->write("Hello,server.I am Client");
    ui->pushButton->setEnabled(true);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->setText("已连接");
}

void Client::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    tcpSocket->write(text.toUtf8());
    QString s = "Client: " + text;
    ui->textEdit->append(s);
    ui->lineEdit->clear();
}

void Client::deleteLater()
{
    ui->textEdit->append("断开连接");
    tcpSocket->close();
    ui->pushButton_2->setText("server\n已关闭");
    ui->pushButton->setEnabled(false);
    ui->lineEdit->setReadOnly(true);
}

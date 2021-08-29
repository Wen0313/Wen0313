#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->pushButton->setEnabled(false);
    setFixedSize(this->width(),this->height());
    tcpServer = new QTcpServer();
    tcpClient = new QTcpSocket();
}

Server::~Server()
{
    delete ui;
    tcpServer->close();
}

void Server::connectionSlot()
{
    tcpClient = tcpServer->nextPendingConnection();
    tcpClient->write("Hello,I am Server");
    ui->pushButton->setEnabled(true);
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void Server::readData()
{
    QString msg = "from Client: " + dynamic_cast<QTcpSocket*>(sender())->readAll();
    ui->textEdit->append(msg);
}

void Server::initServer()
{
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        QMessageBox::critical(this,tr("Server"),tr("unable to start the server: %l.").arg(tcpServer->errorString()));
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(int i = 0;i < ipAddressList.size(); i++){
        if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address()){
            ipAddress = ipAddressList.at(i).toString();
            break;
        }
    }
    if(ipAddress.isEmpty()) ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//    tcpServer->listen(QHostAddress::Any,tcpServer->serverPort());
    ui->lineEdit_2->setText(ipAddress);
    quint16 port = tcpServer->serverPort();
    ui->lineEdit_3->setText(QString::number(port));
}

void Server::on_pushButton_2_clicked() //启动
{
    initServer();
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(connectionSlot()));
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->setText("运行中");
    QMessageBox::information(this,"Information","启动成功，等待连接");
}

void Server::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    tcpClient->write(text.toUtf8());
    QString s = "Server: " + text;
    ui->textEdit->append(s);
    ui->lineEdit->clear();
}

void Server::deleteLater()
{
    ui->textEdit->append("断开连接");
    ui->pushButton->setEnabled(false);
}

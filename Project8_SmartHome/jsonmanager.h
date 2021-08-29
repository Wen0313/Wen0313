#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

class JsonManager : public QObject
{
    Q_OBJECT
public:
    explicit JsonManager(QObject *parent = nullptr);
    ~JsonManager();
    QStringList getData();
    void sendMessage(const QString& city);
    void jsonFileUnpack();

signals:
    void loadFinished();
public slots:

private:
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QStringList neededInfo;
};

#endif // JSONMANAGER_H

#ifndef HTTPSREQUESTTHREAD_H
#define HTTPSREQUESTTHREAD_H

#include <QThread>
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "windows.h"

class httpsRequestThread : public QThread
{
    Q_OBJECT
public:
    explicit httpsRequestThread(QObject *parent = nullptr);
    httpsRequestThread(const QString& str);
    void run();
    QString getText();
    QString getUrl();
    void onSendHttpsRequest(QString url);

signals:
    void getReplyFinished(httpsRequestThread* t);
public slots:
    void onFinished();
    void onError(const QList<QSslError> &errors);
private:
    QString text;
    QString url;
};

#endif // HTTPSREQUESTTHREAD_H

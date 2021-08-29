#include "httpsrequestthread.h"

httpsRequestThread::httpsRequestThread(const QString &str)
{
    url = str;
}

void httpsRequestThread::run()
{
    onSendHttpsRequest(url);
}

QString httpsRequestThread::getText()
{
    return text;
}

QString httpsRequestThread::getUrl()
{
    return url;
}

void httpsRequestThread::onSendHttpsRequest(QString url)
{
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    //发送https请求前准备工作
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);

    request.setUrl(QUrl(url));
    QByteArray data;
    QNetworkReply *pReply = pManager->post(request, data);

    /*http://qtbig.com/2019/10/26/qt/qt_5_12_0_and_1_network_bugs/
    Qt 5.12部分版本网络模块重大缺陷
    使用Qt 5.12.0或Qt 5.12.1网络模块进行网络请求操作时报错，导致的后果是请求无法进行。
    错误描述：使用了QNetworkAccessManager的get，post网络请求接口。报下列错误：
    QNetworkReplyHttpImplPrivate::_q_startOperation was called more than once QUrl*/

    //奇怪的是 我用post似乎正常 但是用get会碰到上述问题
    //QNetworkReply *pReply = pManager->get(request);

    connect(pReply, &QNetworkReply::finished, this, &httpsRequestThread::onFinished);
    connect(pReply, &QNetworkReply::sslErrors, this, &httpsRequestThread::onError);
}

void httpsRequestThread::onFinished()
{
    QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
    //保存接收的数据;
    QByteArray replyContent = pReplay->readAll();
    text = QString::fromUtf8(replyContent);
    emit getReplyFinished(this);
}

void httpsRequestThread::onError(const QList<QSslError> &errors)
{
    QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
    //输出错误码及错误信息;
    qDebug()<< errors;
    text = pReplay->errorString();
    emit getReplyFinished(this);
}

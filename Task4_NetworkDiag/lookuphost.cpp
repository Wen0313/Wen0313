#include "lookuphost.h"

LookUpHost::LookUpHost(QObject *parent) : QObject(parent)
{
    info = QHostInfo::fromName("wps.cn");
    hostName = "wps.cn";
    lookedup();
}

LookUpHost::LookUpHost(const QString &text)
{
    info = QHostInfo::fromName(text);
    hostName = text;
    lookedup();
}

void LookUpHost::lookedup()
{
    if(info.error() != QHostInfo::NoError) result = info.errorString() + " ";
    else result = info.addresses().first().toString() + " ";
    result += hostName;
    qDebug() << "result = " << result;
}

QString LookUpHost::getResult()
{
    return result;
}

QString LookUpHost::getHostName()
{
    return hostName;
}

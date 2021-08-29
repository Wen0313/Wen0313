#include "jsonmanager.h"

JsonManager::JsonManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager;
}

JsonManager::~JsonManager()
{
    if(manager){
        delete manager;
        manager = nullptr;
    }
    if(reply){
        delete reply;
        reply = nullptr;
    }
}

QStringList JsonManager::getData()
{
    return neededInfo;
}

void JsonManager::sendMessage(const QString& city)
{
    QString url = "http://wthrcdn.etouch.cn/weather_mini?city=" + city.toUtf8().toPercentEncoding();
    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(reply,&QNetworkReply::finished,this,&JsonManager::jsonFileUnpack);
}

void JsonManager::jsonFileUnpack()
{
    neededInfo.clear();
    QByteArray data = reply->readAll();
    if(!data.contains("invilad-citykey")){ //非法输入
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();
        QJsonObject allData = obj["data"].toObject();

        neededInfo.append(allData["city"].toString()); //城市
        //此时此刻的温度
        QString temp = allData["wendu"].toString();
        QJsonArray arrayData = allData["forecast"].toArray();

        //当天
        allData = arrayData[0].toObject();
        neededInfo.append(allData["date"].toString());//日期
        neededInfo.append(allData["type"].toString() + "/" + temp + "℃");// 类型/温度
        neededInfo.append(allData["high"].toString()+"/"+allData["low"].toString());// 最高/低温
        neededInfo.append(allData["fengxiang"].toString());// 风向

        temp = allData["fengli"].toString();
        temp = temp.mid(9,temp.indexOf("]") - 9);
        neededInfo.append(temp); //风力
    }
    emit loadFinished();
}

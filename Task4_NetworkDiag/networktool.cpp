#include "networktool.h"

NetworkTool::NetworkTool()
{

}

void NetworkTool::executeDiag()
{
    QNetworkConfigurationManager manager;
    if(!manager.isOnline()) {
        result = "网络未连接";
        emit resultIsReady();
        return;
    }

    //获取本机ip 当然 不获取ip也没什么关系
    //不过既然写了 就先留下吧
    QString ip;
    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress addr, info.addresses()){
        if(addr.protocol() == QAbstractSocket::IPv4Protocol)
            ip = addr.toString();
    }
    result = "[" + ip + "] ";

    PingThread* thread = new PingThread();
    thread->setText("www.baidu.com");
    connect(thread,&PingThread::pingFinished,this,&NetworkTool::state);
    thread->run();
}

void NetworkTool::state(const QString& text,int state)
{
    Q_UNUSED(text);
    if(state) result += "网络已连接，互联网访问";
    else result += "网络已连接，但不能访问互联网";
    emit resultIsReady();
}

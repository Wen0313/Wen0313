#include "pingthread.h"

PingThread::PingThread(QObject *parent) : QThread(parent)
{

}

PingThread::~PingThread()
{
    if(cmd){
        delete cmd;
        cmd = nullptr;
    }
}

void PingThread::run()
{
    cmd = new QProcess();
    cmd->start("ping " + text + " -n 2 -w 100");
    cmd->waitForFinished();
    QString result = QString::fromLocal8Bit(cmd->readAll());
    //接入网络但随便设置ip地址ping的结果是找不到主机 而不是丢包
    //不过不确定如果正常ip地址但诸如网络欠费不能访问的情况下能不能找到
    //所以带上了“100%丢失”这种情况
    if(result.contains("找不到主机") || result.contains("100% 丢失"))
        emit pingFinished(text, 0);
    else emit pingFinished(text, 1);
}

void PingThread::setText(const QString &str)
{
    text = str;
}

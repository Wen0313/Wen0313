#include "dnstool.h"

DNSTool::DNSTool()
{
    lookAccount = new LookUpHost("account.wps.cn");
    lookDrive = new LookUpHost("drive.wps.cn");
    lookQing = new LookUpHost("qing.wps.cn");
}

DNSTool::~DNSTool()
{
    if(lookAccount){
        delete lookAccount;
        lookAccount = nullptr;
    }
    if(lookDrive){
        delete lookDrive;
        lookDrive = nullptr;
    }
    if(lookQing){
        delete lookQing;
        lookQing = nullptr;
    }
    if(nt){
        delete nt;
        nt = nullptr;
    }
}

void DNSTool::executeDiag()
{
    //可能没有网络
    nt = new NetworkTool;
    connect(nt,&NetworkTool::resultIsReady,this,&DNSTool::goOn);
    nt->executeDiag();
}

void DNSTool::goOn()
{
    QString networkState = nt->getResult();
    if(!networkState.contains("互联网访问")){
        result = "诊断失败，请检查网络连接";
        emit resultIsReady();
        return;
    }
    result = lookAccount->getResult();
    if(isCorrect(lookAccount)) result += " 域名未被污染\n";
    else result += " 域名被污染\n";
    result += lookDrive->getResult();
    if(isCorrect(lookDrive)) result += " 域名未被污染\n";
    else result += " 域名被污染\n";
    result += lookQing->getResult();
    if(isCorrect(lookQing)) result += " 域名未被污染";
    else result += " 域名被污染";
    emit resultIsReady();
}

bool DNSTool::isCorrect(LookUpHost *ptr)
{
    //去掉hostName 然后对比从两个主流较稳定的dns服务器获取的ip
    //因为我从223.5.5.5拿到的和从114.114.114.114拿到的结果不一样
    //似乎都应该是正确的，所以只要等于其中一个就算是未被污染
    QString check = ptr->getResult().mid(0, ptr->getResult().lastIndexOf(" "));
    QString correct1 = cmdNslookup(ptr->getHostName(),"223.5.5.5");
    QString correct2 = cmdNslookup(ptr->getHostName(),"114.114.114.114");
    if(check != correct1 && check != correct2){
        return false;
    }
    else return true;
}

QString DNSTool::cmdNslookup(const QString& text, const QString& dns)
{
    QProcess* cmd = new QProcess;
    cmd->start("nslookup " + text + " " + dns);
    cmd->waitForFinished();
    QString result = QString::fromLocal8Bit(cmd->readAll());
    int index = result.lastIndexOf("Address:  ") + 10;
    int index2 = result.indexOf("\r\n", index);
    //返回的是dns服务器解析的ip
    return result.mid(index, index2 - index);
}


#include "requesttool.h"

RequestTool::RequestTool()
{
    t1 = new httpsRequestThread("https://account.wps.cn/api/time");
    connect(t1,&httpsRequestThread::getReplyFinished,this,&RequestTool::getText);
    t1->run();
    t2 = new httpsRequestThread("https://drive.wps.cn/api/time");
    connect(t2,&httpsRequestThread::getReplyFinished,this,&RequestTool::getText);
    t2->run();
    t3 = new httpsRequestThread("https://qing.wps.cn/api/time");
    connect(t3,&httpsRequestThread::getReplyFinished,this,&RequestTool::getText);
    t3->run();
}

RequestTool::~RequestTool()
{
    if(t1){
        delete t1;
        t1 = nullptr;
    }
    if(t2){
        delete t2;
        t2 = nullptr;
    }
    if(t3){
        delete t3;
        t3 = nullptr;
    }
}

void RequestTool::executeDiag()
{

}

void RequestTool::getText(httpsRequestThread* t)
{
    QString s = t->getText();
    qDebug() << "s = " << s;
    result += t->getUrl();
    if(s.contains("ok"))
        result += " https请求已连通\n";
    else result += " https请求未连通\n";
    getCount++;
    if(getCount == 3) emit resultIsReady();
}

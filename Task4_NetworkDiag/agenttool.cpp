#include "agenttool.h"

AgentTool::AgentTool()
{

}

void AgentTool::executeDiag()
{
    QProcess* cmd = new QProcess();
    cmd->start("netsh winhttp show proxy");
    cmd->waitForFinished();
    QString res = QString::fromLocal8Bit(cmd->readAll());
    if(res.contains("没有代理服务器")){
        result = "WinHttp 代理未启用";
        emit resultIsReady();
    }
    else {
        result = "WinHttp 代理已启用";
        deleteAgent();
    }
}

void AgentTool::deleteAgent()
{
    QProcess* cmd = new QProcess();
    cmd->start("netsh winhttp reset proxy");
    cmd->waitForFinished();
    QString res = QString::fromLocal8Bit(cmd->readAll());
    qDebug() << res;
    if(res.contains("没有代理服务器")){
        result += "\n已为您自动清除代理设置（现在没有代理了）";
    }
    else result += "\n清除代理设置失败（需要以管理员身份运行）";
    emit resultIsReady();
}

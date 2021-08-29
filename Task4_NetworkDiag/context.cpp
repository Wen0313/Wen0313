#include "context.h"

Context::Context()
{

}

Context::Context(int index)
{
    //策略与简单工厂结合
    //将实例化具体工具的过程由widget转移到context类中
    switch(index){
    case 0:
        tool = new NetworkTool;
        break;
    case 1:
        tool = new AgentTool;
        break;
    case 2:
        tool = new DNSTool;
        break;
    case 3:
        tool = new HostsTool;
        break;
    case 4:
        tool = new RequestTool;
        break;
    }
}

Context::~Context()
{
    if(tool){
        delete tool;
        tool = nullptr;
    }
}

void Context::contextInterface()
{
    if(tool) tool->executeDiag();
}

QString Context::contextResult()
{
    qDebug() << "contextResult = " << tool->getResult();
    return tool->getResult();
}

DiagnosticTools *Context::getTool()
{
    return tool;
}

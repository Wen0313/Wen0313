#ifndef CONTEXT_H
#define CONTEXT_H
#include <QObject>
#include "diagnostictools.h"
#include "networktool.h"
#include "agenttool.h"
#include "dnstool.h"
#include "requesttool.h"
#include "hoststool.h"

//Context上下文类
//用一个具体工具来配置
//维护一个DiagnosticTools对象的父类指针
class Context:public QObject
{
    Q_OBJECT
public:
    Context();
    Context(int index);
    ~Context();

    void contextInterface(); //上下文接口
    QString contextResult();
    DiagnosticTools* getTool();//用来connect

private:
    DiagnosticTools* tool = nullptr;
};

#endif // CONTEXT_H

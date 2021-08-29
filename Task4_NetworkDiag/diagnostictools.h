#ifndef DIAGNOSTICTOOLS_H
#define DIAGNOSTICTOOLS_H

#include <QObject>
#include <QNetworkConfigurationManager>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QHostInfo>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include "windows.h"

//策略模式：定义了算法家族，分别封装起来，
//让他们之间可以互相替换。
//此模式让算法的变化不会影响到使用算法的客户

//诊断工具类，定义所有支持的算法的公共接口
class DiagnosticTools : public QObject
{
    Q_OBJECT
public:
    explicit DiagnosticTools(QObject *parent = nullptr);
    virtual ~DiagnosticTools();
    virtual void executeDiag() = 0 ;
    virtual QString getResult();

signals:
    void resultIsReady();

public slots:
protected:
    QString result;
};

#endif // DIAGNOSTICTOOLS_H

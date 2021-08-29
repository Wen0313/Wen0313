#ifndef HOSTSTOOL_H
#define HOSTSTOOL_H
#include "diagnostictools.h"
#include "dnstool.h"
#include "networktool.h"
#include <QFile>
#include <QTextStream>

class HostsTool : public DiagnosticTools
{
public:
    HostsTool();
    ~HostsTool();
    void executeDiag();
    void allResult();

public slots:
    void goOn();

private:
    DNSTool* tool = nullptr;
    NetworkTool* nt = nullptr;
    QString all;
};

#endif // HOSTSTOOL_H

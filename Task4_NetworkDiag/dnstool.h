#ifndef DNSTOOL_H
#define DNSTOOL_H

#include "diagnostictools.h"
#include "lookuphost.h"
#include "networktool.h"

class DNSTool : public DiagnosticTools
{
public:
    DNSTool();
    ~DNSTool();
    void executeDiag();
    bool isCorrect(LookUpHost* ptr);
    QString cmdNslookup(const QString& text, const QString& dns);

public slots:
    void goOn();
private:
    LookUpHost* lookAccount = nullptr;
    LookUpHost* lookDrive = nullptr;
    LookUpHost* lookQing = nullptr;
    NetworkTool* nt = nullptr;
};

#endif // DNSTOOL_H

#ifndef NETWORKTOOL_H
#define NETWORKTOOL_H
#include "diagnostictools.h"
#include "pingthread.h"

class NetworkTool : public DiagnosticTools
{
public:
    NetworkTool();
    void executeDiag();
public slots:
    void state(const QString& text, int state);
};

#endif // NETWORKTOOL_H

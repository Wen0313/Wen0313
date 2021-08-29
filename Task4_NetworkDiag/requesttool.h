#ifndef REQUESTTOOL_H
#define REQUESTTOOL_H
#include "diagnostictools.h"
#include "httpsrequestthread.h"
#include "networktool.h"

class RequestTool : public DiagnosticTools
{
public:
    RequestTool();
    ~RequestTool();
    void executeDiag();
public slots:
    void getText(httpsRequestThread* t);
    void goOn();
private:
    httpsRequestThread* t1,*t2,*t3;
    NetworkTool* nt = nullptr;
    int getCount = 0;
};

#endif // REQUESTTOOL_H

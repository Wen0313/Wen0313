#ifndef AGENTTOOL_H
#define AGENTTOOL_H
#include "diagnostictools.h"

class AgentTool : public DiagnosticTools
{
public:
    AgentTool();
    void executeDiag();
    void deleteAgent(); //自动清除代理设置
};

#endif // AGENTTOOL_H

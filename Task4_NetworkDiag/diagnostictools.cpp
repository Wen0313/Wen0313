#include "diagnostictools.h"

DiagnosticTools::DiagnosticTools(QObject *parent) : QObject(parent)
{

}

DiagnosticTools::~DiagnosticTools()
{

}

QString DiagnosticTools::getResult()
{
    return result;
}

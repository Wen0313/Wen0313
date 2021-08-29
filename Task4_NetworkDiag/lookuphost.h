#ifndef LOOKUPHOST_H
#define LOOKUPHOST_H

#include <QObject>
#include <QHostInfo>

class LookUpHost : public QObject
{
    Q_OBJECT
public:
    explicit LookUpHost(QObject *parent = nullptr);
    LookUpHost(const QString& text);
    QString getResult();
    QString getHostName();
    void lookedup();

private:
    QString result;
    QString hostName;
    QHostInfo info;
};

#endif // LOOKUPHOST_H

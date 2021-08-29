#ifndef PINGTHREAD_H
#define PINGTHREAD_H

#include <QThread>
#include <QProcess>

class PingThread : public QThread
{
    Q_OBJECT
public:
    explicit PingThread(QObject *parent = nullptr);
    ~PingThread();
    void run();
    void setText(const QString& str);

signals:
    void pingFinished(const QString& text,int state);

private:
    QProcess* cmd;
    QString text;
};

#endif // PINGTHREAD_H

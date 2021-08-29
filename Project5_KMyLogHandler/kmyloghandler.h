#ifndef KMYLOGHANDLER_H
#define KMYLOGHANDLER_H

#include <QObject>
#include <QFile>
#include <QFileSystemWatcher>
#include <QTextStream>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>

class KMyLogHandler : public QObject
{
    Q_OBJECT
public:
    explicit KMyLogHandler(QObject *parent = nullptr);
    ~KMyLogHandler();
    QFileSystemWatcher* getFileWatcher();
//    QString getText();

    //打开
    void openLog();

    //关闭
    void closeLog();

    //文本格式读
    QString readText();

    //文本格式写
    void writeText(const QString& text);

    //二进制读
    QString readData();

    //二进制写
    void writeData(const QString& text);

signals:

public slots:

private:
    QFileSystemWatcher* m_fileWatcher;
    QString m_currentTime;
};


#endif // KMYLOGHANDLER_H

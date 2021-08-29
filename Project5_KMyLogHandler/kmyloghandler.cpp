#include "kmyloghandler.h"

KMyLogHandler::KMyLogHandler(QObject *parent) : QObject(parent)
{
    m_fileWatcher = new QFileSystemWatcher();
}

KMyLogHandler::~KMyLogHandler()
{

}

QFileSystemWatcher* KMyLogHandler::getFileWatcher()
{
    return m_fileWatcher;
}

//QString KMyLogHandler::getText() //最头一行  不用了
//{
//    QFile file("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.txt");
//    if (file.open(QFile::ReadOnly))
//    {
//        QTextStream out(&file);
//        m_text = out.readLine();
//        /*以下注释是获取最后一行的  保留一下
//        auto len = file.size();
//        int i = 3;
//        file.seek(len-i);
//        while (QString(file.readLine()).compare("\n") != 0)
//        {
//            i++;
//            file.seek(len - i);
//        }
//        m_text = file.readLine();
//        m_text.chop(1);*/
//        file.close();
//    }
//    return m_text;
//}

void KMyLogHandler::openLog()
{

}

void KMyLogHandler::closeLog()
{

}

QString KMyLogHandler::readText()
{
    QFile file("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.txt");
    file.open(QFile::ReadOnly);
    QString m_txtContent = file.readAll();
    file.close();
    return m_txtContent;
}

void KMyLogHandler::writeText(const QString& text)
{
    m_currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.z");
    QFile file("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.txt");
    file.open(QFile::ReadWrite);
    QTextStream out(&file);
    QString temp = out.readAll();//file.readAll();
    file.resize(0);
    out << m_currentTime << "  " << text << "\n";
    out << temp;
    file.close();
}

QString KMyLogHandler::readData()
{
    QFile file("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.dat");
    file.open(QFile::ReadOnly);
    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);
    QString m;
    in >> m;
    QStringList m_text;
    m_text.append(m);
    while(true){
        in >> m;
        if(m.size() == 0) break;
        m_text.append(m);
    }
    m = "";
    for(int i = 0;i < m_text.size(); i++){
        m += m_text.at(i);
    }

    file.close();
    return m;
}

void KMyLogHandler::writeData(const QString& text)
{
    m_currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.z");
    QFile file("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.dat");
    file.open(QFile::ReadWrite);
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);
    QString m_datContent = readData();
    QString str = m_currentTime + " " + text + "\n";
    file.resize(0);
    out << m_currentTime + " " + text + "\n";
    out << m_datContent;
    file.close();
}

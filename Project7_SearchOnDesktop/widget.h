#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QtWin>
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfoList>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QFileSystemWatcher>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QTextCodec>
#include <QMessageBox>
#include <QVector>
#include <QAbstractNativeEventFilter>
#include <QTableWidget>
#include "windows.h"
#include "dialog.h"
#include "selectpath.h"
#include <QtCore/qmath.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget,public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void insertToTable(const QString& _name); //找到合适的位置插入一行
    int strCompare(const QString& text,const QString& name); //判断是否匹配 并获取优先级

    //以下函数用来获取汉字首字母
    QString getSpell(const QString& str);
    char transform(quint16 nCode);

    QStringList getSelectedItemsNames();
    //热键事件
    bool nativeEventFilter(const QByteArray &eventType,void *message,long *result);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_directoryChanged();

    void actionOpen();

    void actionRemove();

    void actionRename();

    void renameStart();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void pathChange();

private:
    Ui::Widget *ui;
    QString location; //桌面路径
    QStringList allFileNames; //桌面路径下的所有文件或文件夹的名字列表
    QFileSystemWatcher *m_pathWatcher; //目录监控
    QMenu *m_menu; //右键菜单
    QVector<int> pro; //展示优先级
    Dialog *renameDialog = nullptr; //重命名窗口
    selectPath* selectWidget = nullptr; //选择路径
};

#endif // WIDGET_H

#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Search on the desktop");
    w.setWindowIcon(QIcon(":/new/prefix1/image/1625111176881.jpg"));
    w.setWindowState(Qt::WindowMinimized); //窗口默认隐藏
    a.installNativeEventFilter(&w); //监视本地事件
    w.show();

    return a.exec();
}

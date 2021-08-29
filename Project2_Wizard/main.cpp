#include "widget.h"
#include "wizard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wizard w;
    w.setWindowTitle("界面安装");
    w.show();
    w.button(QWizard::NextButton)->setEnabled(false);

    return a.exec();
}

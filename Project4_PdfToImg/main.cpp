#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load("pdftoimg.qm", a.applicationDirPath());
    a.installTranslator(&qtTranslator);

    Dialog w;
    w.show();

    return a.exec();
}

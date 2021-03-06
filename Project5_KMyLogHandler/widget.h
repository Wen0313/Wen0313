#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "kmyloghandler.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_fileChanged();

    void on_datFileChanged();

    void on_pushButton_3_clicked();

    void on_textEdit_textChanged();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    KMyLogHandler mylog;
    KMyLogHandler mydatlog;
};

#endif // WIDGET_H

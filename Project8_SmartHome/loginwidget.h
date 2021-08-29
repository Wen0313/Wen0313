#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QDebug>
#include "menu.h"
#include <QMessageBox>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void initStyle();

private slots:
    void on_pushButton_clicked();

    void menuExit();

private:
    Ui::LoginWidget *ui;
    Menu* menu = nullptr;
};

#endif // LOGINWIDGET_H

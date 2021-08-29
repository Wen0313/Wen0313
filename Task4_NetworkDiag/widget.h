#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QList>
#include "context.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void diagnosticOne();
    void deleteLastLine();
    void isEnabled(bool is);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void textReady();

private:
    Ui::Widget *ui;
    Context* currentContext = nullptr;
    QList<QThread*> threadList;
};

#endif // WIDGET_H

#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event);

signals:
    void clicked(bool);
public slots:
};

#endif // MYPUSHBUTTON_H

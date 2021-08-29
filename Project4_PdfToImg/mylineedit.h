#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QMouseEvent>

class mylineedit : public QLineEdit
{
    Q_OBJECT
public:
    explicit mylineedit(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event);

signals:
    void clicked(bool);
public slots:
};

#endif // MYLINEEDIT_H

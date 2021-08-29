#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QMouseEvent>

class mycombobox : public QComboBox
{
    Q_OBJECT
public:
    mycombobox(QWidget* parent=0);
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked(bool);
};

#endif // MYCOMBOBOX_H

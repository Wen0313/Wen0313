#include "mylineedit.h"

mylineedit::mylineedit(QWidget *parent) : QLineEdit(parent)
{

}

void mylineedit::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setStyleSheet("color:black");
        emit clicked(true);
    }
    QLineEdit::mousePressEvent(event);
}

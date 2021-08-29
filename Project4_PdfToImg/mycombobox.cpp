#include "mycombobox.h"

mycombobox::mycombobox(QWidget *parent) : QComboBox(parent)
{

}


void mycombobox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked(true);
    }
    QComboBox::mousePressEvent(event);
}

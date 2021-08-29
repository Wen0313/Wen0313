#include "mypushbutton.h"

mypushbutton::mypushbutton(QWidget *parent) : QPushButton(parent)
{

}

void mypushbutton::mousePressEvent(QMouseEvent *event)
{
    if(event -> button() == Qt::LeftButton){
        emit clicked(true);
    }
    QPushButton::mousePressEvent(event);
}

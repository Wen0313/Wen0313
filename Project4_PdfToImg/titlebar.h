#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QMainWindow>
#include <QFrame>
#include <QMouseEvent>

class Titlebar : public QFrame
{
public:
    Titlebar(QWidget *parent);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
     bool m_isPressed;
     QPoint m_startMovePos;
};

#endif // TITLEBAR_H

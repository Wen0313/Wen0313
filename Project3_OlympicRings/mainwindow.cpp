#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox_2->setCheckState(Qt::Checked);
    ui->checkBox_3->setCheckState(Qt::Checked);
    ui->checkBox_4->setCheckState(Qt::Checked);
    ui->checkBox_5->setCheckState(Qt::Checked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setViewport(50, 50, width() - 100, height() - 100);
    painter.setWindow(-10, 5, 20, -10);
    painter.setPen(QPen(QBrush(Qt::gray), 1 / (width() - 100) / 20));
    painter.drawLine(-10, 0, 10, 0);
    painter.setPen(QPen(QBrush(Qt::gray), 1 / (height() - 100) / 8));
    painter.drawLine(0, -5, 0, 5);

    drawCircleBlue();
    drawCircleBlack();
    drawCircleRed();
    drawCircleYellow();
    drawCircleGreen();
}

void MainWindow::drawCircleBlue()
{
    if(m_blue){
        QPainter painter(this);
        painter.setViewport(50, 50, width() - 100, height() - 100);
        painter.setPen(QPen(QBrush(Qt::blue), 10));
        QRectF rectangle(width() / 2 - 50 - 120, height() / 2 - 50, 100, 100);
        painter.drawEllipse(rectangle);
    }
}

void MainWindow::drawCircleBlack()
{
    if(m_black){
        QPainter painter(this);
        painter.setViewport(50, 50, width() - 100, height() - 100);
        painter.setPen(QPen(QBrush(Qt::black), 10));
        QRectF rectangle(width() / 2 - 50, height() / 2 - 50, 100, 100);
        painter.drawEllipse(rectangle);
    }
}

void MainWindow::drawCircleRed()
{
    if(m_red){
        QPainter painter(this);
        painter.setViewport(50, 50, width() - 100, height() - 100);
        painter.setPen(QPen(QBrush(Qt::red), 10));
        QRectF rectangle(width() / 2 - 50 + 120, height() / 2 - 50, 100, 100);
        painter.drawEllipse(rectangle);
    }
}

void MainWindow::drawCircleYellow()
{
    if(m_yellow){
        QPainter painter(this);
        painter.setViewport(50, 50, width() - 100, height() - 100);
        painter.setPen(QPen(QBrush(Qt::yellow), 10));
        QRectF rectangle(width() / 2 - 110, height() / 2 + 10, 100, 100);
        painter.drawEllipse(rectangle);
    }
}

void MainWindow::drawCircleGreen()
{
    if(m_green){
        QPainter painter(this);
        painter.setViewport(50, 50, width() - 100, height() - 100);
        painter.setPen(QPen(QBrush(Qt::green), 10));
        QRectF rectangle(width() / 2 + 10, height() / 2 + 10, 100, 100);
        painter.drawEllipse(rectangle);
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    m_blue = arg1 == Qt::Checked;
    update();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    m_black = arg1 == Qt::Checked;
    update();
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    m_red = arg1 == Qt::Checked;
    update();
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    m_yellow = arg1 == Qt::Checked;
    update();
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    m_green = arg1 == Qt::Checked;
    update();
}

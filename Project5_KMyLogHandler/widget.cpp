#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    setFixedSize(this->width(),this->height());

    mylog.getFileWatcher()->addPath("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.txt");
    connect(mylog.getFileWatcher(), SIGNAL(fileChanged(QString)), this, SLOT(on_fileChanged()));
    mydatlog.getFileWatcher()->addPath("C:\\Users\\3G7K8F3\\Desktop\\kscampus\\myqt\\Project5_KMyLogHandler\\test\\test.dat");
    connect(mydatlog.getFileWatcher(), SIGNAL(fileChanged(QString)), this, SLOT(on_datFileChanged()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    mylog.writeText(text);
}

void Widget::on_fileChanged()
{
    ui->textEdit->setText(mylog.readText());
}

void Widget::on_datFileChanged()
{
    ui->textEdit->setText(mydatlog.readData());
}

void Widget::on_pushButton_3_clicked()
{
    ui->textEdit->setText(mylog.readText());
}

void Widget::on_textEdit_textChanged()
{
    ui->textEdit->moveCursor(QTextCursor::NoMove);
}

void Widget::on_pushButton_4_clicked()
{
    ui->textEdit->setText(mydatlog.readData());
}

void Widget::on_pushButton_2_clicked()
{
    QString text = ui->lineEdit->text();
    mydatlog.writeData(text);
}

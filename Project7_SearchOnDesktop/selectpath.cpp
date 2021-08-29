#include "selectpath.h"
#include "ui_selectpath.h"

selectPath::selectPath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectPath)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->pushButton_2->setEnabled(false);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
    QPixmap pixmap(":/new/prefix1/image/4.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);
}

selectPath::~selectPath()
{
    delete ui;
}

QString selectPath::getNewPath()
{
    return newPath;
}

void selectPath::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"open","C:/");
    ui->lineEdit->setText(path);
    if(ui->lineEdit->text() != "") ui->pushButton_2->setEnabled(true);
    else ui->pushButton_2->setEnabled(false);
}

void selectPath::on_pushButton_2_clicked()
{
    newPath = ui->lineEdit->text();
    emit OKClicked();
}

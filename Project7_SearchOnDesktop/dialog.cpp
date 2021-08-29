#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    QPixmap pixmap(":/new/prefix1/image/4.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getText()
{
    return text;
}

void Dialog::initLineEdit(const QString &text)
{
    ui->lineEdit->setText(text);
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == static_cast<QAbstractButton*>(ui->buttonBox->button(QDialogButtonBox::Ok))){
        text = ui->lineEdit->text();
        emit OKClicked();
    }
}

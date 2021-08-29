#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    connect(ui->pushButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏

    connect(ui->comboBox,SIGNAL(clicked(bool)),this,SLOT(holdOn())); //以下六条为了让点击其他按钮的时候最上面二选一的大按钮不会被取消
    connect(ui->comboBox_2,SIGNAL(clicked(bool)),this,SLOT(holdOn()));
    connect(ui->lineEdit,SIGNAL(clicked(bool)),this,SLOT(holdOn()));
    connect(ui->lineEdit_2,SIGNAL(clicked(bool)),this,SLOT(holdOn()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(holdOn()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(holdOn()));

    connect(ui->lineEdit,SIGNAL(clicked(bool)),this,SLOT(lineEditClear()));

    ui->pushButton_4->setDown(true);
    ui->label->setText(tr("Output as picture"));
    ui->label_2->setText(tr("Watermark content"));
    ui->label_3->setText(tr("Save to"));
    ui->label_4->setText(tr("Format"));
    ui->label_5->setText(tr("Picture quality"));
    ui->pushButton_3->setText(tr("Output"));
    ui->lineEdit->setText(tr("Secret、No copying、Original、Sample"));
    ui->comboBox->addItem(tr("Hd Quility"));
    ui->comboBox->addItem(tr("Common Quality"));
    ui->comboBox_2->addItem("PNG");
    ui->comboBox_2->addItem("JPG");
    ui->comboBox_2->addItem("TMP");
    initStyle();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initStyle(){
    QFile qss(":/mainwindow.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    qApp->setStyleSheet(stylesheet);
    qss.close();
}


void Dialog::on_pushButton_4_clicked()
{
    leftDown = true;
    ui->pushButton_4->setDown(true);
    ui->pushButton_5->setDown(false);
}

void Dialog::on_pushButton_5_clicked()
{
    leftDown = false;
    ui->pushButton_5->setDown(true);
    ui->pushButton_4->setDown(false);
}

void Dialog::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    ui->lineEdit_2->setText(path);
}

void Dialog::holdOn()
{
    if(leftDown) ui->pushButton_4->setDown(true);
    else ui->pushButton_5->setDown(true);
}

void Dialog::lineEditClear(){
    if(ui->lineEdit->text() == "保密、严禁复制、原件、样件") ui->lineEdit->clear();
}

void Dialog::on_pushButton_3_clicked()
{
    QDir dir = ui->lineEdit_2->text();
    if(dir.exists()){
        QMessageBox::information(new Dialog,"information","output success");
    }
    else QMessageBox::critical(this,"error","path error");
}

#include "wizard.h"
#include <QMessageBox>
#include <QWizardPage>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <windows.h>

Wizard::Wizard(QWidget *parent):
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->lineEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
    ui->pushButton->setEnabled(false);
    setFixedSize(this->width(),this->height());

    ui->comboBox->addItem("序列号");
    ui->comboBox->addItem("账号登陆");
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setMaxLength(16);
    ui->lineEdit_3->setMaxLength(12);
    ui->lineEdit_2->setMaxLength(19);
    ui->lineEdit_2->setInputMask(">AAAAA-AAAA-AAAAA-AAAAA;#");
    ui->progressBar->setValue(0);

    connect(ui->checkBox,SIGNAL(checked()),this,SLOT(on_checkBox_stateChanged(int arg1)));//阅读协议
    connect(ui->pushButton,SIGNAL(clicked),this,SLOT(on_pushButton_clicked())); //安装位置
    connect(ui->comboBox,SIGNAL(on_comboBox_currentIndexChanged()),ui->stackedWidget,SLOT(setCurrentIndex(int)));//激活方式选择
    connect(ui->pushButton_2,SIGNAL(clicked),this,SLOT(on_pushButton_2_clicked()));//激活按钮
    connect(ui->checkBox_6,SIGNAL(checked()),this,SLOT(on_checkBox_6_stateChanged(int)));//跳过激活
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(path);
    if(ui->lineEdit->text().length() > 0){
        button(QWizard::NextButton)->setEnabled(true);
    }
}

void Wizard::on_pushButton_2_clicked()
{
    if(ui->stackedWidget->currentIndex() == 1 && ui->lineEdit_2->text().length() < 22){ //序列号登录
        QMessageBox::critical(this,"error","请输入完整的序列号");
        return;
    }
    if(ui->stackedWidget->currentIndex() == 0 && (ui->lineEdit_3->text().length() == 0 || ui->lineEdit_4->text().length() == 0)){
        QMessageBox::critical(this,"error","请输入账号密码");
        return;
    }
    QMessageBox::information(this,"information","激活成功！");
    if(ui->stackedWidget->currentIndex() == 1) ui->lineEdit_2->setReadOnly(true);
    if(ui->stackedWidget->currentIndex() == 0){
        ui->lineEdit_3->setReadOnly(true);
        ui->lineEdit_4->setReadOnly(true);
    }
    button(QWizard::FinishButton)->setEnabled(true);
    button(QWizard::CancelButton)->setEnabled(false);
    button(QWizard::BackButton)->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->checkBox_6->setEnabled(false);
}


void Wizard::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0) button(QWizard::NextButton)->setEnabled(false);
    else {
        button(QWizard::NextButton)->setEnabled(true);
    }
}

void Wizard::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "序列号") ui->stackedWidget->setCurrentIndex(1);
    else ui->stackedWidget->setCurrentIndex(0);
}

void Wizard::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1 == 0) button(QWizard::FinishButton)->setEnabled(false);
    else {
        button(QWizard::FinishButton)->setEnabled(true);
    }
}

void Wizard::installStart()
{
    button(QWizard::NextButton)->setEnabled(false);
    ui->textEdit_2->setText("");
    QDir dir(ui->lineEdit->text());

    QFileInfoList list = dir.entryInfoList();
    int file_count = list.count();

    for(int i = 0; i < file_count; i++)
    {
        QFileInfo file_info = list.at(i);
        if(i == 1) continue;
        QString absolute_file_path = file_info.absoluteFilePath();
        ui->textEdit_2->insertPlainText(absolute_file_path);
        Sleep(50);
        ui->textEdit_2->insertPlainText("\n");
        int per = (i + 1) * 100 / file_count; //进度百分比 per%
        ui->progressBar->setValue(per);
    }
    if(file_count == 2) ui->progressBar->setValue(100);
    button(Wizard::BackButton)->setEnabled(false);
    button(Wizard::NextButton)->setEnabled(true);
}


void Wizard::on_Wizard_currentIdChanged(int id)
{
    if(id != 0) this->button(QWizard::NextButton)->setEnabled(false);
    if(id == 3) {
        this->button(QWizard::FinishButton)->setEnabled(false);
        this->button(QWizard::BackButton)->setEnabled(false);
    }
    if(id == 2) installStart();
}

void Wizard::on_radioButton_clicked()
{
    ui->pushButton->setEnabled(true);
}

void Wizard::on_radioButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
}

void Wizard::on_textEdit_2_textChanged() //总是显示最下面的内容
{
    ui->textEdit_2->moveCursor(QTextCursor::End);
}

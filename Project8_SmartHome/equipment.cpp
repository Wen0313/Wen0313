#include "equipment.h"
#include "ui_equipment.h"

Equipment::Equipment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipment)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("Equipment");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider_2->setMaximum(100);
    ui->horizontalSlider_3->setMaximum(100);

    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider_2->setEnabled(false);
    ui->horizontalSlider_3->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->display(16);
    initStyle();
}

Equipment::~Equipment()
{
    delete ui;
}

void Equipment::initStyle()
{
    QPixmap pixmap(":/images/8.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);

    QFile qss(":/Equipment.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    qss.close();
}

//返回
void Equipment::on_pushButton_6_clicked()
{
    emit ReturnClicked();
    this->close();
}

//主灯开关
void Equipment::on_pushButton_clicked()
{
    QString text;
    if(!e_1){ //按之前是关的
        text = "主灯打开";
        ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                      "border-image: url(:/images/on.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_5->setStyleSheet("QLabel#label_5{"
                                   "border-image: url(:/images/l1On.png);}");
        ui->horizontalSlider->setStyleSheet("QSlider::handle:horizontal {"
                                            "border: 0px ;"
                                            "border-image:  url(:/images/handle.png);"
                                            "width: 15px;"
                                            "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        int val = ui->horizontalSlider->value();
        text = tr("主灯当前亮度 %1").arg(val);
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider->setEnabled(true);

    }else{
        text = "主灯关闭";
        ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                      "border-image: url(:/images/off.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_5->setStyleSheet("QLabel#label_5{"
                                   "border-image: url(:/images/l1Off.png);}");
        ui->horizontalSlider->setStyleSheet("QSlider::handle:horizontal {"
                                            "border: 0px ;"
                                            "border-image:  url(:/images/handle-disabled.png);"
                                            "width: 15px;"
                                            "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider->setEnabled(false);
    }
    e_1 = !e_1;
}

//主灯亮度条
void Equipment::on_horizontalSlider_valueChanged(int value)
{
    QString text = tr("主灯当前亮度 %1").arg(value);
    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
}

//射灯开关
void Equipment::on_pushButton_2_clicked()
{
    QString text;
    if(!e_2){ //按之前是关的
        text = "射灯打开";
        ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                      "border-image: url(:/images/on.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_6->setStyleSheet("QLabel#label_6{"
                                   "border-image: url(:/images/l2On.png);}");
        ui->horizontalSlider_2->setStyleSheet("QSlider::handle:horizontal {"
                                              "border: 0px ;"
                                              "border-image:  url(:/images/handle.png);"
                                              "width: 15px;"
                                              "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        int val = ui->horizontalSlider_2->value();
        text = tr("射灯当前亮度 %1").arg(val);
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider_2->setEnabled(true);

    }else{
        text = "射灯关闭";
        ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2 {"
                                      "border-image: url(:/images/off.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_6->setStyleSheet("QLabel#label_6{"
                                   "border-image: url(:/images/l2Off.png);}");
        ui->horizontalSlider_2->setStyleSheet("QSlider::handle:horizontal {"
                                              "border: 0px ;"
                                              "border-image:  url(:/images/handle-disabled.png);"
                                              "width: 15px;"
                                              "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider_2->setEnabled(false);
    }
    e_2 = !e_2;
}

//射灯亮度条
void Equipment::on_horizontalSlider_2_valueChanged(int value)
{
    QString text = tr("射灯当前亮度 %1").arg(value);
    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
}

//音响开关
void Equipment::on_pushButton_3_clicked()
{
    QString text;
    if(!e_3){ //按之前是关的
        text = "音响打开";
        ui->pushButton_3->setStyleSheet("QPushButton#pushButton_3 {"
                                      "border-image: url(:/images/on.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_7->setStyleSheet("QLabel#label_7{"
                                   "border-image: url(:/images/soundOn.png);}");
        ui->horizontalSlider_3->setStyleSheet("QSlider::handle:horizontal {"
                                              "border: 0px ;"
                                              "border-image:  url(:/images/handle.png);"
                                              "width: 15px;"
                                              "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        int val = ui->horizontalSlider_3->value();
        text = tr("音响当前音量 %1").arg(val);
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider_3->setEnabled(true);

    }else{
        text = "音响关闭";
        ui->pushButton_3->setStyleSheet("QPushButton#pushButton_3 {"
                                      "border-image: url(:/images/off.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_7->setStyleSheet("QLabel#label_7{"
                                   "border-image: url(:/images/soundOff.png);}");
        ui->horizontalSlider_3->setStyleSheet("QSlider::handle:horizontal {"
                                              "border: 0px ;"
                                              "border-image:  url(:/images/handle-disabled.png);"
                                              "width: 15px;"
                                              "margin: -7px -7px -7px -7px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        ui->horizontalSlider_3->setEnabled(false);
    }
    e_3 = !e_3;
}

//音响音量条
void Equipment::on_horizontalSlider_3_valueChanged(int value)
{
    QString text = tr("音响当前音量 %1").arg(value);
    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
}

//空调开关
void Equipment::on_pushButton_4_clicked()
{
    QString text;
    if(!e_4){ //按之前是关的
        text = "空调打开";
        ui->pushButton_4->setStyleSheet("QPushButton#pushButton_4 {"
                                      "border-image: url(:/images/on.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_8->setStyleSheet("QLabel#label_8{"
                                   "border-image: url(:/images/airOn.png);}");
        ui->spinBox->setEnabled(true);
        ui->spinBox->setStyleSheet("QSpinBox::up-button{"
                                   "border-image:url(:/images/up.png);"
                                   "height: 15px;}"
                                   "QSpinBox::down-button{"
                                   "border-image:url(:/images/down.png);"
                                   "height: 15px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
        int val = ui->spinBox->value();
        text = tr("空调当前温度 %1").arg(val);
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();

    }else{
        text = "空调关闭";
        ui->pushButton_4->setStyleSheet("QPushButton#pushButton_4 {"
                                      "border-image: url(:/images/off.png);"
                                      "border-width:0px 0px 0px 0px;"
                                      "background-repeat:none;"
                                      "background-origin: content;}");
        ui->label_8->setStyleSheet("QLabel#label_8{"
                                   "border-image: url(:/images/airOff.png);}");
        ui->spinBox->setEnabled(false);
        ui->spinBox->setStyleSheet("QSpinBox::up-button{"
                                   "border-image:url(:/images/up-disabled.png);"
                                   "height: 15px;}"
                                   "QSpinBox::down-button{"
                                   "border-image:url(:/images/down-disabled.png);"
                                   "height: 15px;}");
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
    }
    e_4 = !e_4;
}

void Equipment::on_spinBox_valueChanged(int arg1)
{
    QString text;
    text = tr("空调当前温度 %1").arg(arg1);
    ui->lcdNumber->display(arg1);
    ui->listWidget->addItem(text);
    ui->listWidget->scrollToBottom();
    if(arg1 == 30) {
        text = "已经是最高温度";
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
    }
    else if(arg1 == 16){
        text = "已经是最低温度";
        ui->listWidget->addItem(text);
        ui->listWidget->scrollToBottom();
    }
}

void Equipment::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
}

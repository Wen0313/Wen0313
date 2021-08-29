#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("Weather");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    initStyle();
}

Weather::~Weather()
{
    delete ui;
    if(jManager){
        delete jManager;
        jManager = nullptr;
    }
}

void Weather::initStyle()
{
    QPixmap pixmap(":/images/5.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);

    QFile qss(":/Weather.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    qss.close();
}

//查询
void Weather::on_pushButton_clicked()
{
    jManager = new JsonManager;
    connect(jManager,&JsonManager::loadFinished,this,&Weather::setText);
    QString city = ui->lineEdit->text();
    jManager->sendMessage(city);

}

//返回
void Weather::on_pushButton_2_clicked()
{
    emit ReturnClicked();
    this->close();
}

void Weather::setText()
{
    QStringList info = jManager->getData();
    if(info.empty()){
        ui->label_14->setText("-");
        ui->label_8->setText("-");
        ui->label_9->setText("-");
        ui->label_10->setText("-");
        ui->label_11->setText("-");
        ui->label_12->setText("-");
        QMessageBox::critical(this,"Error","invalid-citykey");
        return;
    }
    ui->label_14->setText(info.at(0));
    ui->label_8->setText(info.at(1));
    ui->label_9->setText(info.at(2));
    ui->label_10->setText(info.at(3));
    ui->label_11->setText(info.at(4));
    ui->label_12->setText(info.at(5));
}

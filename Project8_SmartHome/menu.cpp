#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("Menu");
    initStyle();
}

Menu::~Menu()
{
    emit exit();
    delete ui;
    if(musicPlayer){
        delete musicPlayer;
        musicPlayer = nullptr;
    }
    if(weather){
        delete weather;
        weather = nullptr;
    }
    if(equipment){
        delete equipment;
        equipment = nullptr;
    }
}

void Menu::initStyle()
{

    QPixmap pixmap(":/images/3.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);

    QFile qss(":/Menu.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    qss.close();
}

//设备控制
void Menu::on_pushButton_clicked()
{
    if(equipment == nullptr){
        equipment = new Equipment;
        connect(equipment,&Equipment::ReturnClicked,this,&QWidget::show);
    }
    equipment->show();
    this->close();
}

//天气查询
void Menu::on_pushButton_2_clicked()
{
    if(weather == nullptr){
        weather = new Weather;
        connect(weather,&Weather::ReturnClicked,this,&QWidget::show);
    }
    weather->show();
    this->close();
}

//音乐播放
void Menu::on_pushButton_3_clicked()
{
    if(musicPlayer == nullptr) {
        musicPlayer = new MusicPlayer;
        connect(musicPlayer,&MusicPlayer::ReturnClicked,this,&QWidget::show);
    }
    musicPlayer->show();
    this->close();
}

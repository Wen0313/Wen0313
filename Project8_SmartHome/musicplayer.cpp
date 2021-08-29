#include "musicplayer.h"
#include "ui_musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("Music Player");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    initStyle();
    path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); //桌面路径
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_2->setText(path);
    ui->verticalSlider->setMaximum(100);
    initWidget();
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
    if(player){
        delete player;
        player = nullptr;
    }
    if(mediaList){
        delete mediaList;
        mediaList = nullptr;
    }
    if(currentItem){
        delete currentItem;
        currentItem = nullptr;
    }
}

void MusicPlayer::initStyle()
{
    QPixmap pixmap(":/images/6.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);
    ui->listWidget->setStyleSheet("background: transparent");

    QFile qss(":/MusicPlayer.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    qss.close();
}

void MusicPlayer::initWidget()
{
    ui->listWidget->clear();
    if(player){
        delete player;
        player = nullptr;
    }
    if(!mediaList) mediaList = new QMediaPlaylist;
    else mediaList->clear();

    QDir dir(path);
    QStringList list;
    list << "*.mp3";
    dir.setNameFilters(list);
    list = dir.entryList();
    if(list.empty()) {
        isReady(false);
        return;
    }
    for(auto name:list){
        ui->listWidget->addItem(name);
        mediaList->addMedia(QUrl::fromLocalFile(path + "/" + name));
    }
    currentItem = ui->listWidget->item(0);
    ui->listWidget->setItemSelected(currentItem,true);
    player = new QMediaPlayer(this);
    connect(player,&QMediaPlayer::currentMediaChanged,this,&MusicPlayer::currentChanged);
    player->setPlaylist(mediaList);
    ui->verticalSlider->setValue(40);
    ui->lineEdit->setText("40");
    player->setVolume(40);
    isReady(true);
    ui->pushButton_2->setEnabled(false);
}

void MusicPlayer::setPlayStyle()
{
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "border-image: url(:/images/play.png);"
                                  "border-width:0px 0px 0px 0px;"
                                  "background-repeat:none;"
                                  "background-origin: content;}");
    ui->pushButton->setStyleSheet("QPushButton#pushButton:hover {"
                                  "border-image: url(:/images/play-hover.png);}");
}

void MusicPlayer::setPauseStyle()
{
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "border-image: url(:/images/pause.png);"
                                  "border-width:0px 0px 0px 0px;"
                                  "background-repeat:none;"
                                  "background-origin: content;}");
    ui->pushButton->setStyleSheet("QPushButton#pushButton:hover {"
                                  "border-image: url(:/images/pause-hover.png);}");
}

void MusicPlayer::isReady(bool flag)
{
    ui->pushButton->setEnabled(flag); // 播放 上一曲 下一曲
    ui->pushButton_2->setEnabled(flag);
    ui->pushButton_3->setEnabled(flag);
    ui->pushButton_4->setEnabled(flag);//+ - 滚动条
    ui->pushButton_5->setEnabled(flag);
    ui->verticalSlider->setEnabled(flag);
}

//返回
void MusicPlayer::on_pushButton_6_clicked()
{
    emit ReturnClicked();
    this->close();
}

//播放
void MusicPlayer::on_pushButton_clicked()
{
    if(player->state() != QMediaPlayer::PlayingState) {
        player->play();
        setPauseStyle();
    }
    else {
        player->pause();
        setPlayStyle();
    }
}

//上一曲
void MusicPlayer::on_pushButton_2_clicked()
{
    mediaList->setCurrentIndex(mediaList->currentIndex() - 1);
    player->play();
}

//下一曲
void MusicPlayer::on_pushButton_3_clicked()
{
    mediaList->setCurrentIndex(mediaList->currentIndex() + 1);
    player->play();
}

//滚动条调音量
void MusicPlayer::on_verticalSlider_valueChanged(int value)
{
    player->setVolume(value);
    ui->lineEdit->setText(QString::number(value));
    if(value == 100) ui->pushButton_4->setEnabled(false);
    else if(value == 0) ui->pushButton_5->setEnabled(false);
    else{
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
}

//音量+
void MusicPlayer::on_pushButton_4_clicked()
{
    int volume = ui->lineEdit->text().toInt();
    player->setVolume(volume + 1);
    ui->verticalSlider->setValue(volume + 1);
    ui->lineEdit->setText(QString::number(volume + 1));
}

//音量-
void MusicPlayer::on_pushButton_5_clicked()
{
    int volume = ui->lineEdit->text().toInt();
    player->setVolume(volume - 1);
    ui->verticalSlider->setValue(volume - 1);
    ui->lineEdit->setText(QString::number(volume - 1));
}

//单击选中播放
void MusicPlayer::on_listWidget_itemClicked(QListWidgetItem *item)
{
    setPauseStyle();
    int row = ui->listWidget->row(item);
    if(row == 0) ui->pushButton_2->setEnabled(false);
    else ui->pushButton_2->setEnabled(true);
    currentItem = item;
    mediaList->setCurrentIndex(row);
    player->play();
}

//选择目录
void MusicPlayer::on_pushButton_7_clicked()
{
    QString old = path;
    path = QFileDialog::getExistingDirectory(this);
    if(path == "") path = old;
    ui->lineEdit_2->setText(path);
    initWidget();
}

//切换曲目
void MusicPlayer::currentChanged()
{
    int row_media = mediaList->currentIndex();
    if(row_media == 0) ui->pushButton_2->setEnabled(false);
    else ui->pushButton_2->setEnabled(true);
    currentItem = ui->listWidget->item(row_media);
    ui->listWidget->setItemSelected(currentItem, true);
    setPauseStyle();
}

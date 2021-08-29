#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QDir>
#include <QFile>
#include <QMediaPlaylist>
#include <QListWidgetItem>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer();
    void initStyle();
    void initWidget();
    void setPlayStyle();
    void setPauseStyle();
    void isReady(bool flag);

signals:
    void ReturnClicked();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_7_clicked();

    void currentChanged();

private:
    Ui::MusicPlayer *ui;
    QMediaPlayer* player = nullptr;
    QMediaPlaylist* mediaList = nullptr;
    QListWidgetItem* currentItem = nullptr;
    QString path;
};

#endif // MUSICPLAYER_H

#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "musicplayer.h"
#include "weather.h"
#include "equipment.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void initStyle();
signals:
    void exit();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Menu *ui;
    MusicPlayer* musicPlayer = nullptr;
    Weather* weather = nullptr;
    Equipment* equipment = nullptr;
};

#endif // MENU_H

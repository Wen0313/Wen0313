#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include "jsonmanager.h"

namespace Ui {
class Weather;
}

class Weather : public QWidget
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
    void initStyle();

signals:
    void ReturnClicked();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void setText();

private:
    Ui::Weather *ui;
    JsonManager* jManager;
};

#endif // WEATHER_H

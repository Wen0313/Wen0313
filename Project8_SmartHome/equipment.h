#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QWidget>
#include <QLCDNumber>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Equipment;
}

class Equipment : public QWidget
{
    Q_OBJECT

public:
    explicit Equipment(QWidget *parent = nullptr);
    ~Equipment();
    void initStyle();

signals:
    void ReturnClicked();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_horizontalSlider_3_valueChanged(int value);

    void on_pushButton_4_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_5_clicked();

private:
    Ui::Equipment *ui;
    bool e_1 = false; //主灯
    bool e_2 = false; //射灯
    bool e_3 = false; //音响
    bool e_4 = false; //空调
};

#endif // EQUIPMENT_H

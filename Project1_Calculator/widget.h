#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_m_1_clicked();

    void on_m_2_clicked();

    void on_m_3_clicked();

    void on_m_4_clicked();

    void on_m_5_clicked();

    void on_m_6_clicked();

    void on_m_7_clicked();

    void on_m_8_clicked();

    void on_m_9_clicked();

    void on_m_add_clicked();

    void on_m_sub_clicked();

    void on_m_del_clicked();

    void on_m_end_clicked();

    void on_m_0_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

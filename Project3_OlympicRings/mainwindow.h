#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    void drawCircleBlue();
    void drawCircleBlack();
    void drawCircleRed();
    void drawCircleYellow();
    void drawCircleGreen();

    bool m_blue=false;
    bool m_black = false;
    bool m_red = false;
    bool m_yellow = false;
    bool m_green = false;
};

#endif // MAINWINDOW_H

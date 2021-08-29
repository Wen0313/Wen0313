#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTranslator>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void initStyle();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void holdOn();

    void lineEditClear();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    bool leftDown = true;
};

#endif // DIALOG_H

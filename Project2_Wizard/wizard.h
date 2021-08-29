#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>
#include "ui_wizard.h"
#include <QFileDialog>
namespace Ui {
class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = nullptr);
    ~Wizard();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void installStart();

    void on_Wizard_currentIdChanged(int id);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_textEdit_2_textChanged();

private:
    Ui::Wizard *ui;
};

#endif // WIZARD_H

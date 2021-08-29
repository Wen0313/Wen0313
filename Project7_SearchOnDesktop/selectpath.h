#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QWidget>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class selectPath;
}

class selectPath : public QWidget
{
    Q_OBJECT

public:
    explicit selectPath(QWidget *parent = nullptr);
    ~selectPath();
    QString getNewPath();

signals:
    void OKClicked();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::selectPath *ui;
    QString newPath;
};

#endif // SELECTPATH_H

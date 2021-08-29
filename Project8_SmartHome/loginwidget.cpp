#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    this->setWindowIcon(QIcon(":/images/1.jpg"));
    ui->lineEdit->setText("administrator");
    ui->lineEdit_2->setText("123456");
    initStyle();
}

LoginWidget::~LoginWidget()
{
    delete ui;
    if(menu){
        delete menu;
        menu = nullptr;
    }
}

void LoginWidget::initStyle()
{
    QPixmap pixmap(":/images/2.jpg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);

    QFile qss(":/LoginWidget.qss");
    qss.open(QFile::ReadOnly);
    QTextStream filetext(&qss);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    qss.close();
}

void LoginWidget::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == "administrator" && ui->lineEdit_2->text() == "123456"){
        this->close();
        menu = new Menu;
        connect(menu,&Menu::exit,this,&LoginWidget::menuExit);
        menu->show();
    }else{
        QMessageBox::critical(this,"Error","Input error,login failed");
    }
}

void LoginWidget::menuExit()
{
    exit(0);
}

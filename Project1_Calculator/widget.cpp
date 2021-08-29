#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->m_1, SIGNAL(clicked), this, SLOT(on_m_1_clicked()));
    connect(ui->m_2, SIGNAL(clicked), this, SLOT(on_m_2_clicked()));
    connect(ui->m_3, SIGNAL(clicked), this, SLOT(on_m_3_clicked()));
    connect(ui->m_4, SIGNAL(clicked), this, SLOT(on_m_4_clicked()));
    connect(ui->m_5, SIGNAL(clicked), this, SLOT(on_m_5_clicked()));
    connect(ui->m_6, SIGNAL(clicked), this, SLOT(on_m_6_clicked()));
    connect(ui->m_7, SIGNAL(clicked), this, SLOT(on_m_7_clicked()));
    connect(ui->m_8, SIGNAL(clicked), this, SLOT(on_m_8_clicked()));
    connect(ui->m_9, SIGNAL(clicked), this, SLOT(on_m_9_clicked()));
    connect(ui->m_0, SIGNAL(clicked), this, SLOT(on_m_0_clicked()));
    connect(ui->m_add, SIGNAL(clicked), this, SLOT(on_m_add_clicked()));
    connect(ui->m_sub, SIGNAL(clicked), this, SLOT(on_m_sub_clicked()));
    connect(ui->m_del, SIGNAL(clicked), this, SLOT(on_m_del_clicked()));
    connect(ui->m_end, SIGNAL(clicked), this, SLOT(on_m_end_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_m_1_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = ""; //如果已经计算过一次了，那么刷新文本框
    s += "1";
    ui->m_show->setText(s);
}

void Widget::on_m_2_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "2";
    ui->m_show->setText(s);
}

void Widget::on_m_3_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "3";
    ui->m_show->setText(s);
}

void Widget::on_m_4_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "4";
    ui->m_show->setText(s);
}

void Widget::on_m_5_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "5";
    ui->m_show->setText(s);
}

void Widget::on_m_6_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "6";
    ui->m_show->setText(s);
}

void Widget::on_m_7_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "7";
    ui->m_show->setText(s);
}

void Widget::on_m_8_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "8";
    ui->m_show->setText(s);
}

void Widget::on_m_9_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    s += "9";
    ui->m_show->setText(s);
}

void Widget::on_m_add_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    if(s.size() >= 1 && (s[s.size() - 1] == "+" || s[s.size() - 1] == "-")) s=s.left(s.size() - 1);
    s += "+";
    ui->m_show->setText(s);
}

void Widget::on_m_sub_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    if(s.size() >= 1 && (s[s.size() - 1] == "+" || s[s.size() - 1] == "-")) s=s.left(s.size() - 1);
    s += "-";
    ui->m_show->setText(s);
}

void Widget::on_m_del_clicked()
{
    ui->m_show->setText("");
}

void Widget::on_m_end_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) return;
    QString res = s; //暂存文本
    if(s.indexOf("+") == -1 && s.indexOf("-") == -1) { //如果没有+-号
        res += "= " + QString::number(res.toLongLong());
        ui->m_show->setText(res);
        return;
    }
    if(s.at(s.size() - 1) == "+" || s.at(s.size() - 1) == "-"){ //如果最后一位是+-号
        res += "= 未输入完成";
        ui->m_show->setText(res);
        return;
    }
    QString temp;
    long long sum = 0;
    int loc = 0;
    long long num;
    bool isNegtive = false;
    if(s.at(0) == "-") {
        isNegtive = true;
        loc++;
    }
    for(; loc < s.size(); loc++){
        temp = "0";
        while(loc < s.size() && s.at(loc) != "+" && s.at(loc) != "-"){
            temp += s.at(loc);
            loc++;
        }
        num = temp.toLongLong();
        if(temp.size() > 2 && !num) {
            res += ("= longlong都溢出了呀");
            ui->m_show->setText(res);
            return;
        }
        sum += isNegtive? -num: num;
        if(loc == s.size()) break;
        isNegtive = s.at(loc) == "+" ?false : true;
    }
    res += ("= " + QString::number(sum));
    ui->m_show->setText(res);
}

void Widget::on_m_0_clicked()
{
    QString s=ui->m_show->text();
    if(s.indexOf("=") != -1) s = "";
    if((s.size() == 1 && s[0] == "0") || (s.size() >= 2 && s[s.size() - 1] == "0" && (s[s.size() - 2] == "+" || s[s.size() - 2] == "-"))){
            ui->m_show->setText(s);
    }else{
        s += "0";
        ui->m_show->setText(s);
    }
}

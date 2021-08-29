#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("WPS Diagnostic Tools");
    setFixedSize(this->width(),this->height());
    for(int i = 0;i < 5; i++) {
        QThread* thread = new QThread();
        threadList.push_back(thread);
    }

    ui->comboBox->addItem("检测网络是否接入/连通");
    ui->comboBox->addItem("检测是否使用了代理");
    ui->comboBox->addItem("检测DNS解析wps域名是否正确");
    ui->comboBox->addItem("配置hosts");
    ui->comboBox->addItem("检测域名请求是否连通");
    ui->textEdit->setReadOnly(true);
//    ui->textEdit->setStyleSheet("background: transparent;");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

Widget::~Widget()
{
    delete ui;
    if(currentContext){
        delete currentContext;
        currentContext = nullptr;
    }
    for(auto c:threadList){
        if(c){
            delete c;
            c = nullptr;
        }
    }
}

void Widget::diagnosticOne()
{
    ui->textEdit->setTextColor(Qt::black);
    ui->textEdit->append(tr("[%1] \n诊断中，请稍等...").arg(ui->comboBox->currentText()));

    int index = ui->comboBox->currentIndex();
    if(currentContext) delete currentContext;
    currentContext = new Context(index);

    //moveToThread
    currentContext->moveToThread(threadList[index]);
    QCoreApplication::processEvents();

    connect(currentContext->getTool(),&DiagnosticTools::resultIsReady,this,&Widget::textReady);
    Sleep(200);
    //统一的接口
    currentContext->contextInterface();
}

void Widget::textReady()
{
    deleteLastLine();
    int index = ui->comboBox->currentIndex();
    QString text = currentContext->contextResult();
    //设置颜色
    if(text.contains("不能") || text.contains("未连接")
            || text.contains("失败") || text.contains("域名被污染")
            || text.contains("未连通"))
        ui->textEdit->setTextColor(Qt::red);
//    else if(text.contains("管理员身份")) ui->textEdit->setTextColor(Qt::yellow);
    else ui->textEdit->setTextColor(Qt::green);

    ui->textEdit->append(text);
    if(index != 4) ui->textEdit->append("\n");
    isEnabled(true);
}

void Widget::deleteLastLine()
{
    ui->textEdit->setFocus();
    QTextCursor cur = ui->textEdit->textCursor();
    ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    ui->textEdit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
    ui->textEdit->textCursor().removeSelectedText();
    ui->textEdit->textCursor().deletePreviousChar();
    ui->textEdit->setTextCursor(cur);
}

void Widget::isEnabled(bool is)
{
    ui->pushButton->setEnabled(is);
    ui->pushButton_2->setEnabled(is);
    ui->comboBox->setEnabled(is);
}

void Widget::on_pushButton_clicked()
{
    isEnabled(false);
    ui->textEdit->clear();
    ui->textEdit->setAlignment(Qt::AlignCenter);
    diagnosticOne();
}

void Widget::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setAlignment(Qt::AlignCenter);
    for(int i = 0;i < 5; i++){
        isEnabled(false);
        ui->comboBox->setCurrentIndex(i);
        diagnosticOne();
        Sleep(200);
    }
}

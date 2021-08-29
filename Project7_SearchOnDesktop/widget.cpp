#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pathWatcher = new QFileSystemWatcher;
    //生成右键菜单
    m_menu = new QMenu(ui->tableWidget);
    QAction *action = new QAction("打开",this);
    connect(action,&QAction::triggered,this,&Widget::actionOpen);
    m_menu->addAction(action);
    action = new QAction("重命名",this);
    connect(action,&QAction::triggered,this,&Widget::actionRename);
    m_menu->addAction(action);
    action = new QAction("删除",this);
    connect(action,&QAction::triggered,this,&Widget::actionRemove);
    m_menu->addAction(action);

    QPixmap pixmap(":/new/prefix1/image/4.jpeg");
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);
    QFont font("bold");
    ui->pushButton->setFont(font);
    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                                  "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能对表格内容进行修改
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);//允许接收requested信号
    ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableWidget->setShowGrid(false); //不显示表格线
    ui->tableWidget->setColumnWidth(0,200); //名称列宽度
    ui->tableWidget->setColumnWidth(1,280); //路径列宽度

    location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); //桌面路径
    m_pathWatcher->addPath(location);
    connect(m_pathWatcher,&QFileSystemWatcher::directoryChanged,this,&Widget::on_directoryChanged);
    QDir dir(location);
    QStringList list = dir.entryList();
    for(int i = 2;i < list.size(); i++){
        allFileNames.append(list[i]);
        //在tablewidget添加一行
        insertToTable(list[i]);
    }
    //注册热键 Alt+Space
    bool ok = RegisterHotKey(nullptr,1,MOD_ALT | MOD_NOREPEAT,VK_SPACE);
    if(!ok) exit(0);
}

Widget::~Widget()
{
    delete ui;
    if(m_pathWatcher){
        delete m_pathWatcher;
        m_pathWatcher = Q_NULLPTR;
    }
    if(m_menu){
        delete m_menu;
        m_menu = Q_NULLPTR;
    }
    UnregisterHotKey(nullptr,1);
}

void Widget::insertToTable(const QString &_name)
{
    if(_name == "") return;
    int row = 0;  //要插入到的行数
    QString text = ui->lineEdit->text();
    if(text == "")
        ui->tableWidget->insertRow(row);
    else{  //找到合适的插入位置
        QString nameWithoutType = _name.mid(0,_name.lastIndexOf("."));
        if(!strCompare(text,_name)) return;//不匹配则判断下一个
        else if(!text.compare(nameWithoutType)){ //完全匹配 区分大小写
            pro.insert(0,0);  //因为不匹配返回了0，所以完全匹配优先级设置为0，最优先展示
            row = 0;
        }
        else{
            int priority = strCompare(text,_name);
            if(pro.isEmpty()) pro.push_back(priority);
            else{
                int i = 0;
                for(; i < pro.size(); i++){
                    if(priority < pro[i]){
                        row = i;
                        pro.insert(i,priority);
                        break;
                    }
                }
                if(i == pro.size()){
                    row = i;
                    pro.push_back(priority);
                }
            }
        }
        ui->tableWidget->insertRow(row);
    }

    QString name = location + "/" + _name; //完整路径
    //下面设置第一列的图标和名字
    QFileInfo file_info(name);
    QFileIconProvider icon_provider;
    QIcon icon = icon_provider.icon(file_info);
    QString type = icon_provider.type(file_info); //获取文件类型
    QTableWidgetItem * item = new QTableWidgetItem;
    item->setIcon(icon);
    item->setText(_name);
    ui->tableWidget->setItem(row, 0,item);

    //下面设置第二列的路径
    ui->tableWidget->setItem(row, 1,new QTableWidgetItem(location));

    //下面设置第三列的大小，跳过文件夹
    if(type == "File Folder") return;
    QFile file(name);
    long long size;
    if (QFileInfo(file).isSymLink()) { //获取快捷方式的准确大小，而不是链接目标的大小
        QFile f(name);
        f.open(QFile::ReadOnly);
        size = f.size();
        f.close();
    }
    else size = file.size();
    if(size < 1024){
        ui->tableWidget->setItem(row, 2,new QTableWidgetItem(QString::number(size) + "  B"));
    }else if(size < qPow(1024,2)){
        double kb = size / 1024; //展示KB大小
        ui->tableWidget->setItem(row, 2,new QTableWidgetItem(QString::number(kb) + "  KB"));
    }else if(size < qPow(1024,3)){
        double mb = size / qPow(1024,2); //展示MB大小
        ui->tableWidget->setItem(row, 2,new QTableWidgetItem(QString::number(mb) + "  MB"));
    }else{
        double gb = size / qPow(1024,3); //展示GB大小
        ui->tableWidget->setItem(row, 2,new QTableWidgetItem(QString::number(gb) + "  GB"));
    }
}

//搜索时的匹配算法
//如果不匹配返回0  如果匹配则返回优先级，数字越小优先级越高
int Widget::strCompare(const QString &text, const QString &name)
{
    if(text == "") return 1;
    //name如果包含中文则判断首字母能不能匹配成功 不区分大小写
    if(name.contains(QRegExp("[\\x4e00-\\x9fa5]+"))){  //正则表达式用来判断名称里是否含中文
        QString spell = getSpell(name);
        if(spell.indexOf(text,0,Qt::CaseInsensitive) == 0) return name.size();
    }

    //以下是模糊匹配 且不区分大小写
    int current = 0, res = 0;
    for(int i = 0;i < text.size(); i++){
        QString change = ""; //用来保存大写或小写后的text[i]
        if(text[i] >= 'a' && text[i] <= 'z')
            change = text[i].toUpper();
        if(text[i] >= 'A' && text[i] <= 'Z')
            change = text[i].toLower();
        if(change == ""){ //说明第i位输入不是字母 那么直接匹配
            int index = name.indexOf(text[i],current);
            if(index == -1) return 0;
            if(i == 0 && index) res = 10 * index + name.size();
            else res += ((index - current == 0)?1: (80 * (index - current))) + name.size();
            current = index + 1;
            continue;
        }
        //大小写都匹配一次
        int index1 = name.indexOf(text[i],current);
        int index2 = name.indexOf(change,current);
        int index = -1;
        if(index1 == -1 || index2 == -1){
            index = index1 == -1? index2: index1;
        }else{
            index = index1 < index2? index1: index2;
        }
        if(index == -1) return 0;
        if(i == 0 && index) res = 10 * index + name.size();
        else res += ((index - current == 0)?1: (80 * (index - current))) + name.size();
        current = index + 1;
    }
    return res;
}

//把中文变成首字母
QString Widget::getSpell(const QString &str)
{
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    QByteArray buf = gbk->fromUnicode(str);
    quint16* array = new quint16[buf.size() + 1];
    QString res;
    for(int i = 0;i < buf.size(); i++){
        if(static_cast<quint8>(buf[i]) < 0x80){
            //GBK的第一个字节都大于0x81，所以小于直接添加
            res.append(static_cast<char>(buf[i]));
            continue;
        }
        array[i] = static_cast<quint16>((static_cast<quint8>(buf[i])) << 8);
        array[i] |= static_cast<quint8>(buf[i + 1]);
        res.append(transform(array[i]));
        i++;
    }
    delete[] array;
    return res;
}

char Widget::transform(quint16 nCode)  //编码表
{
    if(nCode >= 0xB0A1 && nCode <= 0xB0C4) return 'A';
    if(nCode >= 0XB0C5 && nCode <= 0XB2C0) return 'B';
    if(nCode >= 0xB2C1 && nCode <= 0xB4ED) return 'C';
    if(nCode >= 0xB4EE && nCode <= 0xB6E9) return 'D';
    if(nCode >= 0xB6EA && nCode <= 0xB7A1) return 'E';
    if(nCode >= 0xB7A2 && nCode <= 0xB8C0) return 'F';
    if(nCode >= 0xB8C1 && nCode <= 0xB9FD) return 'G';
    if(nCode >= 0xB9FE && nCode <= 0xBBF6) return 'H';
    if(nCode >= 0xBBF7 && nCode <= 0xBFA5) return 'J';
    if(nCode >= 0xBFA6 && nCode <= 0xC0AB) return 'K';
    if(nCode >= 0xC0AC && nCode <= 0xC2E7) return 'L';
    if(nCode >= 0xC2E8 && nCode <= 0xC4C2) return 'M';
    if(nCode >= 0xC4C3 && nCode <= 0xC5B5) return 'N';
    if(nCode >= 0xC5B6 && nCode <= 0xC5BD) return 'O';
    if(nCode >= 0xC5BE && nCode <= 0xC6D9) return 'P';
    if(nCode >= 0xC6DA && nCode <= 0xC8BA) return 'Q';
    if(nCode >= 0xC8BB && nCode <= 0xC8F5) return 'R';
    if(nCode >= 0xC8F6 && nCode <= 0xCBF9) return 'S';
    if(nCode >= 0xCBFA && nCode <= 0xCDD9) return 'T';
    if(nCode >= 0xCDDA && nCode <= 0xCEF3) return 'W';
    if(nCode >= 0xCEF4 && nCode <= 0xD1B8) return 'X';
    if(nCode >= 0xD1B9 && nCode <= 0xD4D0) return 'Y';
    if(nCode >= 0xD4D1 && nCode <= 0xD7F9) return 'Z';
    return ' ';
}

bool Widget::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG* msg = static_cast<MSG*>(message);

    if(msg->message == WM_HOTKEY){
        if(this->windowState() == Qt::WindowMinimized)
            this->setWindowState(Qt::WindowActive);
        else this->setWindowState(Qt::WindowMinimized);
    }
    return false;
}

void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    //不只删除行里的内容，而是直接删除所有行
    int count = ui->tableWidget->rowCount();
    for(int i = 0;i < count; i++){
        ui->tableWidget->removeRow(0);
    }
    if(arg1 == ""){
        for(int i = 0;i < allFileNames.size(); i++){
            insertToTable(allFileNames[i]);
        }
        return;
    }

    pro.clear();
    for(int i = 0;i < allFileNames.size(); i++){
        insertToTable(allFileNames[i]);
    }

    //一个小彩蛋
    if(arg1 == "作者"){
        QMessageBox::information(this,"一个小彩蛋","作者是王泽文,图标是他常用的头像");
    }
}

void Widget::on_directoryChanged()
{
    //首先找到新增或删除或重命名的文件
    QString name;
    QDir dir(location);
    QStringList list = dir.entryList();

    //需要和搜索框中的内容做匹配
    QString text = ui->lineEdit->text();
    //如果是删除了文件 那么allFileNames中一定更多（一次可能删除多个）
    if(list.size() - 2 < allFileNames.size()){
        while(list.size() - 2 < allFileNames.size()){
            for(int i = 0;i < allFileNames.size(); i++){
                if(!list.contains(allFileNames[i])){
                    name = allFileNames[i];
                    break;
                }
            }
            if(!strCompare(text,name)){ //如果不匹配，那么此时table中没有这一行
                //所以只需要把名字列表中的name去掉即可
                allFileNames.removeOne(name);
                continue;
            }
            else{
                //在pro数组里删掉name对应的优先级
                if(ui->lineEdit->text() != ""){
                    int priority = strCompare(text,name);
                    for(auto it = pro.begin();it != pro.end();it++){
                        if(*it == priority){
                            pro.erase(it);
                            break;
                        }
                    }
                }

                for(int i = 0;i < ui->tableWidget->rowCount(); i++){
                    QTableWidgetItem *item = ui->tableWidget->item(i,0);
                    if(item->data(0).toString() == name){
                        ui->tableWidget->removeRow(i);
                        allFileNames.removeOne(name);
                    }
                }
            }
            if(name == "") return;
        }
        return;
    }

    //如果是新增了文件 那么list中一定更多（一次可能新增多个，如复制）
    if(list.size() - 2 > allFileNames.size()){
        while(list.size() - 2 > allFileNames.size()){
            for(int i = 2; i < list.size(); i++){
                if(!allFileNames.contains(list[i])){
                    name = list[i];
                    break;
                }
            }
            //如果匹配就插入table  插入到合适的位置
            if(strCompare(text,name)){
                insertToTable(name);
            }
            //无论如何名字列表要加上name
            allFileNames.append(name);
            list.removeOne(name);
        }
        return;
    }

    //如果不是删除也不是新增，那就只有是重命名了
    //考虑到更改文件后缀名的情况，直接删除旧名字添加新名字到table中
    QString oldName = "";
    for(int i = 0;i < allFileNames.size(); i++){
        if(!list.contains(allFileNames[i])){
            oldName = allFileNames[i];
            break;
        }
    }
    //如果此时所有条目相等 那么结束这一次执行 因为右键删除的时候已经手动调用过了
    if(oldName == "") return;

    if(!strCompare(text,oldName)){ //如果不匹配，那么此时table中没有这一行
        //所以只需要把名字列表中的name去掉即可
        allFileNames.removeOne(oldName);
    }
    else{
        //在pro数组里删掉name对应的优先级
        int priority = strCompare(text,oldName);
        for(auto it = pro.begin();it != pro.end();it++){
            if(*it == priority){
                pro.erase(it);
                break;
            }
        }

        for(int i = 0;i < ui->tableWidget->rowCount(); i++){
            QTableWidgetItem *item = ui->tableWidget->item(i,0);
            if(item->data(0).toString() == oldName){
                ui->tableWidget->removeRow(i);
                allFileNames.removeOne(oldName);
                break;
            }
        }
    }

    for(int i = 2; i < list.size(); i++){
        if(!allFileNames.contains(list[i])){
            name = list[i];
            break;
        }
    }
    if(strCompare(text,name)){
        insertToTable(name);
    }
    allFileNames.append(name);
}

//为了支持批量打开和批量删除操作
QStringList Widget::getSelectedItemsNames()
{
    auto allFiles = ui->tableWidget->selectedItems();
    QStringList full_info, full_names;
    for(auto item : allFiles){
        QString info = item[0].text();
        full_info.push_back(info);
    }
    for(int i = 0;i < full_info.size(); i++){
        if(full_info[i].indexOf(location) == -1 && full_info[i].indexOf("  B") == -1
                && full_info[i].indexOf("  KB") == -1 && full_info[i].indexOf("  MB") == -1
                && full_info[i].indexOf("  GB") == -1)
            full_names.push_back(location + "/" + full_info[i]);
    }
    return full_names;
}

void Widget::actionOpen()
{
    //支持多选打开
    auto full_names = getSelectedItemsNames();
    if(full_names.size() == 0){
        QMessageBox::critical(this,"Error","Error occurred: There are no files or file folders to open.");
        return;
    }
    for(auto full_name: full_names){
        QDesktopServices::openUrl(QUrl::fromLocalFile(full_name));
    }
}

void Widget::actionRemove()
{
    auto full_names = getSelectedItemsNames();
    if(full_names.size() == 0){
        QMessageBox::critical(this,"Error","Error occurred: There are no files or file folders to remove.");
        return;
    }
    QString message;
    for(auto n: full_names){
        message += n + "\n";
    }
    int res = QMessageBox::question(this,"删除",tr("确实要永久性地删除以下文件吗？\n\n%1").arg(message));
    if(res == QMessageBox::Yes){
        for(auto full_name: full_names){
            QFileInfo fileInfo(full_name);
            bool ok;
            if(fileInfo.isFile()) {
                ok = QFile::remove(full_name);
                if(ok) on_directoryChanged(); //手动调用目录变化函数
                else{
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file [%1] cannot be removed."
                                                          "\nMost likely, the file is in use.").arg(full_name));
                    continue;
                }
            }
            if(fileInfo.isDir()) {
                QDir dir(full_name);
                ok = dir.removeRecursively();
                if(ok) on_directoryChanged();
                else{
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file folder [%1] cannot be removed."
                                                          "\nMost likely, at least one file in this folder is in use.").arg(full_name));
                    continue;
                }
            }
        }
    }
}

void Widget::actionRename()
{
    auto full_names = getSelectedItemsNames();
    if(full_names.size() == 0){
        QMessageBox::critical(this,"Error","Error occurred: There is no file or file folder to rename.");
        return;
    }

    renameDialog = new Dialog(this);
    renameDialog->setWindowModality(Qt::ApplicationModal);
    renameDialog->setWindowTitle("Rename");
    renameDialog->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);
    QString oldName = ui->tableWidget->selectedItems().at(0)->text();
    if(oldName.lastIndexOf(".") != -1){
        oldName = oldName.mid(0,oldName.lastIndexOf("."));
        renameDialog->initLineEdit(oldName);
    }else{
        renameDialog->initLineEdit(oldName);
    }

    renameDialog->show();
    connect(renameDialog,&Dialog::OKClicked,this,&Widget::renameStart);

}

void Widget::renameStart()
{
    QString oldName = location + "/" + ui->tableWidget->selectedItems().at(0)->text();
    QString newName = renameDialog->getText(), newPath;
    if(newName == ""){
        QMessageBox::information(this,"Information","Empty input.\nNothing changed.");
    }
    else if(newName.contains("/") || newName.contains("\\") || newName.contains("*")
            || newName.contains(":") || newName.contains("?") || newName.contains("\"")
            || newName.contains("|") || newName.contains("<") || newName.contains(">")){
        QMessageBox::critical(this,"Error","Error occurred: The file name cannot contain any of the following characters:\n/ \\ \" * < > ? : |");
    }
    else{
        //获取格式 改名不修改文件格式
        int index = oldName.lastIndexOf(".");
        if(index != -1){  //不是文件夹
            QString type = oldName.mid(index,oldName.size() - index);
            newPath = location + "/" + newName + type;
            if(oldName == newPath){
                QMessageBox::information(this,"Information","The old and new names are the same.\nNothing Changed.");
            }else{
                bool ok = QFile::rename(oldName,newPath);
                if(ok){
                    QMessageBox::information(this,"Information","Rename success.");
                }else if(allFileNames.contains(newName+type)){
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file could not be renamed to [%1]."
                                                          "\nA file with the same name exists.\nNothing changed.").arg(newName+type));
                }else{
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file could not be renamed to [%1]."
                                                          "\nMost likely, the file is in use.\nNothing changed.").arg(newName+type));
                }
            }
        }else{  //文件夹改名
            newPath = location + "/" + newName;
            if(oldName == newPath){
                QMessageBox::information(this,"Information","The old and new names are the same.\nNothing Changed.");
            }else{
                bool ok = QFile::rename(oldName,newPath);
                if(ok){
                    QMessageBox::information(this,"Information","Rename success.");
                }else if(allFileNames.contains(newName)){
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file could not be renamed to [%1]."
                                                          "\nA file folder with the same name exists.\nNothing changed.").arg(newName));
                }else{
                    QMessageBox::critical(this,"Error",tr("Error occurred: The file folder could not be renamed to [%1]."
                                                          "\nMost likely, the file folder is in use.\nNothing changed.").arg(newName));
                }
            }
        }
    }

    delete renameDialog;
    renameDialog = nullptr;
}

void Widget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    m_menu->exec(QCursor::pos());
}

void Widget::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
    //鉴于item的文本是针对单元格的，所以不使用item->text(),在整行的任意位置双击都能正确打开文件
    QString name = location + "/" + ui->tableWidget->selectedItems().at(0)->text();
    QDesktopServices::openUrl(QUrl::fromLocalFile(name));
}

void Widget::on_pushButton_clicked()
{
    selectWidget = new selectPath;
    selectWidget->setWindowTitle("Select path");
    selectWidget->setWindowModality(Qt::ApplicationModal);
    selectWidget->setGeometry(this->geometry());
    selectWidget->show();
    connect(selectWidget,&selectPath::OKClicked,this,&Widget::pathChange);
}

void Widget::pathChange()
{
    m_pathWatcher->removePath(location);
    allFileNames.clear();
    ui->lineEdit->clear();
    int count = ui->tableWidget->rowCount();
    for(int i = 0;i < count; i++){
        ui->tableWidget->removeRow(0);
    }

    location = selectWidget->getNewPath();
    delete selectWidget;
    selectWidget = nullptr;

    m_pathWatcher->addPath(location);
    connect(m_pathWatcher,&QFileSystemWatcher::directoryChanged,this,&Widget::on_directoryChanged);
    QDir dir(location);
    QStringList list = dir.entryList();
    for(int i = 2;i < list.size(); i++){
        allFileNames.append(list[i]);
        //在tablewidget添加一行
        insertToTable(list[i]);
    }
}

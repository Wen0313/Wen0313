#include "hoststool.h"

HostsTool::HostsTool()
{

}

HostsTool::~HostsTool()
{
    if(tool){
        delete tool;
        tool = nullptr;
    }
    if(nt){
        delete nt;
        nt = nullptr;
    }
}

void HostsTool::executeDiag()
{
    //可能没有网络
    nt = new NetworkTool;
    connect(nt,&NetworkTool::resultIsReady,this,&HostsTool::goOn);
    nt->executeDiag();
}

void HostsTool::goOn()
{
    QString networkState = nt->getResult();
    if(!networkState.contains("互联网访问")){
        result = "诊断失败，请检查网络连接";
        emit resultIsReady();
        return;
    }
    //鉴于dns获取时总是先从hosts文件中获取
    //为了防止人为修改hosts的错误，先把hosts文件里的相关ip删除
    //然后重新配置
    QFile file("C:/Windows/System32/drivers/etc/hosts");
    //考虑到其他人为操作的情况，这三行即使存在也不一定在最后，所以逐行确认
    bool ok = file.open(QFile::ReadOnly);
    if(ok){
        QTextStream in(&file);
        while(!in.atEnd()){
            QString temp = in.readLine();
            if(temp.size() > 0 && !(temp.at(0) != "#" && (temp.contains("account.wps.cn")
                    || temp.contains("drive.wps.cn") || temp.contains("qing.wps.cn"))))
                all += temp + "\n";
        }
    }else{
        result += "配置hosts失败（指定目录不存在或未找到hosts文件）";
        file.close();
        emit resultIsReady();
        return;
    }
    file.close();

    //清空内容 然后写
    ok = file.open(QFile::WriteOnly | QFile::Truncate);
    if(ok){
        QTextStream out(&file);
        out << all;
    }
    else {
        result += "配置hosts失败（需要以管理员身份运行）";
        emit resultIsReady();
        return;
    }
    file.close();

    tool = new DNSTool();
    tool->executeDiag();
    allResult();
}

void HostsTool::allResult()
{
    result = tool->getResult();
    //每一行单独拿出来判断是否写入
    int index1 = result.indexOf("\n");
    int index2 = result.indexOf("\n", index1 + 1);
    QString one = result.mid(0, index1);
    QString two = result.mid(index1 + 1, index2 - index1 - 1);
    QString three = result.mid(index2 + 1, result.size() - index2 - 1);
    qDebug() << one<<two<<three;

    QFile file("C:/Windows/System32/drivers/etc/hosts");
    //其实如果能运行到这儿了 那么肯定是能打开成功的
    bool ok = file.open(QFile::Append);
    if(ok){
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << "\n";
        result = "";
        int writeCount = 0;
        QString temp;
        if(one.contains("域名未被污染")){
            temp = one.mid(0, one.size() - 6) + "\n";
            out << temp;
            result += temp;
            writeCount++;
        }
        if(two.contains("域名未被污染")){
            temp = two.mid(0, two.size() - 6) + "\n";
            out << temp;
            result += temp;
            writeCount++;
        }
        if(three.contains("域名未被污染")){
            temp = three.mid(0, three.size() - 6) + "\n";
            out << temp;
            result += temp;
            writeCount++;
        }
        out << "\n";
        if(!writeCount) result += "3个域名被污染，未添加至hosts";
        else result += tr("配置hosts成功%1个（已添加/更新至hosts文件）").arg(writeCount);
    }
    else result += "\n配置hosts失败（需要以管理员身份运行）";
    emit resultIsReady();
    file.close();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller=new Controller(this);

    this->enableButton(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

void MainWindow::displayInfo(QString msg)
{
    ui->textBrowser->append(msg);
}

void MainWindow::enableButton(bool b)
{
    // 客户端操作
    ui->actionConnect->setEnabled(b);//建立连接
    ui->actionDisconnct->setEnabled(!b);//断开连接
    ui->actionBuyTicket->setEnabled(!b);//买票
    ui->actionConditionQuery->setEnabled(!b);//条件查询票
    ui->actionAllQuery->setEnabled(!b);//查所有票
}


void MainWindow::on_actionConnect_triggered()
{
    this->displayInfo("正在连接服务器....\n");

    controller->connectServer();
    //this->displayInfo("连接服务器成功....\n");
    this->enableButton(false);
}

void MainWindow::on_actionDisconnct_triggered()
{
    this->displayInfo("正在断开服务器....\n");

    controller->disconnectServer();

    this->displayInfo("断开服务器成功....\n");

    this->enableButton(false);
}

void MainWindow::on_actionBuyTicket_triggered()
{
    this->displayInfo("准备买票....\n");
    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("机票购买");
    QList<QLineEdit*> fields;
    QLineEdit *ord = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入要购买的航班号:"));
    form.addRow(ord);
    QLineEdit *num = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入要购买票的张数:"));
    form.addRow(num);
    fields << ord;
    fields << num;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    /* 点击确认按钮 */
    if (dialog.exec() == QDialog::Accepted)
    {
        QString flightOrd = ord->text();
        QString flightNum = num->text();
        qDebug()<<flightOrd<<"  "<<flightNum;
        /* 获取输入的航班号 */
        unsigned int flightID = flightOrd.toInt();
        unsigned int ticketNum= flightNum.toInt();

        if(-1==controller->buyTicket(flightID,ticketNum))
        {
            this->displayInfo("购票异常...\n");
        }
        connect(controller,&Controller::sendBuyFailure,this,[this](){
            this->displayInfo("购票异常...\n");
        });
        connect(controller,&Controller::sendBuySuccess,this,[this](){
            this->displayInfo("购票成功...\n");
        });
    }
}

void MainWindow::on_actionExit_triggered()
{
    controller->disconnectServer();
    this->close();
}

void MainWindow::on_actionConditionQuery_triggered()
{
    this->displayInfo("Inquire One\n");
    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("机票查询");
    QList<QLineEdit *> fields;
    QLineEdit *ord = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入要查询的航班号:"));
    form.addRow(ord);
    fields << ord;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    /* 点击确认按钮 */
    if (dialog.exec() == QDialog::Accepted)
    {
        int flightID = ord->text().toInt();

        if(controller->conditionQuery(flightID)==-1) {
            displayInfo(ord->text()+"航班查询异常！！");
            return ;
        }

        connect(controller,&Controller::sendQueryFailed,this,[this](){
            this->displayInfo("航班查询异常！！");
        });
        connect(controller,&Controller::sendQuerySuccess,this,[this](){
            this->displayInfo("查询成功...\n");
        });

//        if(message.msg_type==INQUIRE_SUCCEED){
//            sprintf(msg,"查询成功！航班号：%d, 剩余票数：%d, 票价：%d\n",message.flight_ID,message.ticket_num, message.ticket_total_price);
//        }
//        else{
//            sprintf(msg,"查询失败！航班号：%d, 剩余票数：未知\n",message.flight_ID);
//        }
//        display_info(msg);
    }
}

void MainWindow::on_actionAllQuery_triggered()
{
    this->displayInfo("Inquire All....\n");

    if(controller->allQuery()==-1)
    {
        this->displayInfo("查询所有航班信息异常！") ;
        return ;
    }

    connect(controller,&Controller::sendQueryAllFailed,this,[this](){
        this->displayInfo("查询所有航班信息异常！！");
    });
    connect(controller,&Controller::sendQueryAllSuccess,this,[this](){
        this->displayInfo("查询所有航班成功...\n");
    });
//    if(ret==-1) {
//        display_info("接收失败！请重新发送！") ;
//        return ;
//    }
//    pos=0;
//    sprintf(msg,"查询所有航班结果：\n");
//    display_info(msg);
//    for (i=0;i<ret;i=i+sizeof(message)) {
//        memcpy(&message,recv_buf+pos,sizeof(message));
//        if(message.msg_type==INQUIRE_SUCCEED){
//            sprintf(msg,"查询成功！航班号：%d, 剩余票数：%d, 票价：%d",message.flight_ID,message.ticket_num, message.ticket_total_price);
//        }
//        else{
//            sprintf(msg,"查询失败！航班号：%d, 剩余票数：未知",message.flight_ID);
//        }
//        display_info(msg);
//        pos+=sizeof(message);
//    }
//    display_info("\n");
}

void MainWindow::on_actionShow_triggered()
{
    this->displayInfo("Show Message...");
    QDialog dialog((QWidget*)this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("帮助信息");
    form.addRow(new QLabel("<h1><center>功能说明</center></h1>"));
    form.addRow(new QLabel("开启服务器: 启动服务器程序"));
    form.addRow(new QLabel("关闭服务器: 关闭服务器程序"));
    form.addRow(new QLabel("购买机票: 购买机票"));
    form.addRow(new QLabel("特定航班查询: 查询某一特定航班机票信息"));
    form.addRow(new QLabel("所有航班查询: 查询所有航班机票信息"));
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    if (dialog.exec() == QDialog::Accepted)
    {
        displayInfo("查询信息成功\n");
    }
}

void MainWindow::on_actionAbout_triggered()
{
    this->displayInfo("Show About...");
    QDialog dialog((QWidget*)this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("关于");
    form.addRow(new QLabel("<h1>网络售票系统服务端</h1>"));
    form.addRow(new QLabel("<center>版本 V1.0</center>"));
    form.addRow(new QLabel("本程序仅用于测试，请勿用于商业目的"));
    form.addRow(new QLabel("作者信息:XXX"));
    form.addRow(new QLabel("更新日期:XXX"));
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    if (dialog.exec() == QDialog::Accepted)
    {
        this->displayInfo("查询信息成功\n");
    }
}

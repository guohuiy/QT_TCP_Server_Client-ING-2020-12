#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    service=new ThreadService(this);
    this->enableButton(false);

//    connect(service,&ThreadService::dealNewOverMsg,this,[this](QString msg){
//        this->displayInfo(msg);
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayInfo(QString msg)
{
    ui->textBrowser->append(msg);
}

void MainWindow::enableButton(bool boolean)
{
    // 客户端操作
    ui->actionStart->setEnabled(!boolean);
    ui->actionStop->setEnabled(boolean);
    // 机票查询
    ui->actionConditionQuery->setEnabled(boolean);
    ui->actionAllQuery->setEnabled(boolean);
    ui->actionAdd->setEnabled(boolean);
    ui->actionDelete->setEnabled(boolean);
    ui->actionUpdate->setEnabled(boolean);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QVector<QString> msg;
    service->servicePaintEvent(msg);
    foreach(auto m,msg) this->displayInfo(m);
}

void MainWindow::on_actionStart_triggered()
{
    displayInfo("服务器正在开启...");

    //开启监听
    service->listenThread();
    this->displayInfo("服务器开启成功...\n");
//    if(service->listenThread())
//        this->displayInfo("服务器开启成功...\n");
//    else
//        this->displayInfo("服务器开启异常...\n");
    enableButton(true);
}

void MainWindow::on_actionStop_triggered()
{
    this->displayInfo("服务器正在停止...");

    service->serviceStop();
    this->displayInfo("服务器已经停止...");
    this->enableButton(false);
}

void MainWindow::on_actionExit_triggered()
{
    this->displayInfo("\n\n服务器正在退出...\n");

    service->serviceExit();
    this->close();
}

void MainWindow::on_actionConditionQuery_triggered()
{
    this->displayInfo("按条件查询信息...\n");

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
    QObject::connect(&buttonBox,&QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    /* 点击确认按钮 */
    if (dialog.exec() == QDialog::Accepted)
    {
        QString flightMsg;
        if(!service->searchFlightInfo(ord->text().toInt(),flightMsg))
        {
            this->displayInfo("输入的航班号错误！请重新输入！\n");
            return;
        }
        else this->displayInfo(flightMsg);
    }
}

void MainWindow::on_actionAllQuery_triggered()
{
    this->displayInfo("查询所有信息...\n");

    QList<QString> ticketListMsg;

    if(service->searchAllFlight(ticketListMsg))
    {
        foreach(QString msg,ticketListMsg)
        {
            this->displayInfo(msg+"\n");
        }
        this->displayInfo("\n");
    }
    else this->displayInfo("查询信息异常\n");
}

void MainWindow::on_actionShow_triggered()
{
    ui->textBrowser->append("Show Message...");
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
    ui->textBrowser->append("Show About...");
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

void MainWindow::on_actionAdd_triggered()
{
    ui->textBrowser->append("Add Information...");

    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("增加航班信息(管理员)");
    QList<QLineEdit*> fields;
    QLineEdit *id = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入航班号:"));
    form.addRow(id);
    QLineEdit *number = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入票数:"));
    form.addRow(number);
    QLineEdit *price = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入票价:"));
    form.addRow(price);
    fields << id;
    fields << number;
    fields << price;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        unsigned int flightID = id->text().toInt();
        unsigned int ticketNum = number->text().toInt();
        unsigned int ticketPrice = price->text().toInt();

        if(service->addFlightMessage(flightID,ticketNum,ticketPrice))
        {
            this->displayInfo("添加航班信息成功！");
        }
        else
        {
            this->displayInfo("添加航班信息异常！");
        }
    }
}

void MainWindow::on_actionDelete_triggered()
{
    this->displayInfo("Delete Information...");

    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("删除航班信息(管理员)");
    QList<QLineEdit*> fields;
    QLineEdit *id = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入航班号:"));
    form.addRow(id);
    fields << id;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString flightMsg;
        unsigned int flightID = id->text().toInt();
        if(service->searchFlightInfo(flightID,flightMsg))
        {
            this->displayInfo("删除该航班信息："+flightMsg);
            if(service->deleteFlightMessage(flightID))this->displayInfo("删除航班信息成功!\n");
            else this->displayInfo("删除航班信息异常!\n");
        }
        else this->displayInfo("删除航班信息不存在异常!\n"+flightMsg);
    }
}

void MainWindow::on_actionUpdate_triggered()
{
    this->displayInfo("更新信息...");

    QDialog dialog(this);
    QFormLayout form(&dialog);
    dialog.setWindowTitle("更新航班信息(管理员)");
    QList<QLineEdit *> fields;
    QLineEdit *id = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入该航班的航班号:"));
    form.addRow(id);
    QLineEdit *number = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入该航班的票数:"));
    form.addRow(number);
    QLineEdit *price = new QLineEdit(&dialog);
    form.addRow(new QLabel("请输入该航班的票价:"));
    form.addRow(price);
    fields << id;
    fields << number;
    fields << price;
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        int flightID = id->text().toInt();
        int ticketNum = number->text().toInt();
        int ticketPrice = price->text().toInt();
        QString flightMsg;
        if(service->searchFlightInfo(flightID,flightMsg))
        {//有
            this->displayInfo("更新该航班信息："+flightMsg);
            if(service->updateFlightMessage(flightID,ticketNum,ticketPrice)) this->displayInfo("更新航班信息成功!\n");
            else this->displayInfo("更新航班信息异常!\n"+flightMsg);
        }
        else
        {//没有
            if(service->addFlightMessage(flightID,ticketNum,ticketPrice))this->displayInfo("更新航班信息成功!\n");
            else this->displayInfo("航班号："+QString::number(flightID)+" 更新信息异常!\n");
        }
    }
}

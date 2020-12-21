#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(ui->lineEditUsername->text()=="root"&&ui->lineEditPassword->text()=="root")
    {
        this->accept();
    }
    else{
        QMessageBox::warning(this,tr("warning"),tr("user name or password error!"),QMessageBox::Yes);
    }
}

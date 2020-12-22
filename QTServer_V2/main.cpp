#include "mainwindow.h"
#include "login.h"
#include "config.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Config config;
    config.saveConfig();

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("服务器");
    //Login d1;
    //d1.setWindowTitle("管理员");
    //if(d1.exec()==QDialog::Accepted)
    //{
        w.show();
    //}

    return a.exec();
}

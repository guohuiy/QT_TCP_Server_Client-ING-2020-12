#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayInfo(QString msg);
    void enableButton(bool boolean);
    bool listenThread();
    void incomingClientToThreadPool();
protected:
    virtual void paintEvent(QPaintEvent *event); //添加重绘事件

private slots:
    void on_actionStart_triggered();

    void on_actionStop_triggered();

    void on_actionExit_triggered();

    void on_actionConditionQuery_triggered();

    void on_actionAllQuery_triggered();

    void on_actionShow_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    ThreadService *service;
signals:

};
#endif // MAINWINDOW_H

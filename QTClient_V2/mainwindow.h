#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <QMainWindow>

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

private slots:
    void on_actionConnect_triggered();

    void on_actionDisconnct_triggered();

    void on_actionExit_triggered();

    void on_actionConditionQuery_triggered();

    void on_actionAllQuery_triggered();

    void on_actionBuyTicket_triggered();

    void on_actionShow_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    Controller* controller;

};
#endif // MAINWINDOW_H

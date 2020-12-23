/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnct;
    QAction *actionBuyTicket;
    QAction *actionExit;
    QAction *actionConditionQuery;
    QAction *actionAllQuery;
    QAction *actionShow;
    QAction *actionAbout;
    QAction *action;
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuQuery;
    QMenu *menuHelp;
    QMenu *menuOperation;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(781, 638);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnct = new QAction(MainWindow);
        actionDisconnct->setObjectName(QString::fromUtf8("actionDisconnct"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/scissors.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnct->setIcon(icon1);
        actionBuyTicket = new QAction(MainWindow);
        actionBuyTicket->setObjectName(QString::fromUtf8("actionBuyTicket"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBuyTicket->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/power-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionConditionQuery = new QAction(MainWindow);
        actionConditionQuery->setObjectName(QString::fromUtf8("actionConditionQuery"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConditionQuery->setIcon(icon4);
        actionAllQuery = new QAction(MainWindow);
        actionAllQuery->setObjectName(QString::fromUtf8("actionAllQuery"));
        actionAllQuery->setIcon(icon4);
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 50, 761, 501));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 101, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 781, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuQuery = new QMenu(menubar);
        menuQuery->setObjectName(QString::fromUtf8("menuQuery"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuOperation = new QMenu(menubar);
        menuOperation->setObjectName(QString::fromUtf8("menuOperation"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuQuery->menuAction());
        menubar->addAction(menuOperation->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menu->addAction(actionConnect);
        menu->addAction(actionDisconnct);
        menu->addAction(actionExit);
        menuQuery->addAction(actionConditionQuery);
        menuQuery->addAction(actionAllQuery);
        menuHelp->addAction(actionShow);
        menuHelp->addAction(actionAbout);
        menuOperation->addAction(actionBuyTicket);
        toolBar->addAction(actionConnect);
        toolBar->addAction(actionDisconnct);
        toolBar->addAction(actionExit);
        toolBar->addAction(actionConditionQuery);
        toolBar->addAction(actionAllQuery);
        toolBar->addAction(actionBuyTicket);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConnect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        actionDisconnct->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        actionBuyTicket->setText(QApplication::translate("MainWindow", "\350\264\255\344\271\260\346\234\272\347\245\250", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionConditionQuery->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\347\211\271\345\256\232\350\210\252\347\217\255", nullptr));
        actionAllQuery->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\346\211\200\346\234\211\350\210\252\347\217\255", nullptr));
        actionShow->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        action->setText(QApplication::translate("MainWindow", "\350\264\255\344\271\260\346\234\272\347\245\250", nullptr));
        label->setText(QApplication::translate("MainWindow", "\345\256\242\346\210\267\347\253\257\344\277\241\346\201\257\357\274\232", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\345\256\242\346\210\267\347\253\257\346\223\215\344\275\234", nullptr));
        menuQuery->setTitle(QApplication::translate("MainWindow", "\346\234\272\347\245\250\346\237\245\350\257\242", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menuOperation->setTitle(QApplication::translate("MainWindow", "\346\234\272\347\245\250\350\264\255\344\271\260", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

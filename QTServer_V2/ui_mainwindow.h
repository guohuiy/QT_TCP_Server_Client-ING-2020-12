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
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionExit;
    QAction *actionConditionQuery;
    QAction *actionAllQuery;
    QAction *actionShow;
    QAction *actionAbout;
    QAction *actionAdd;
    QAction *actionDelete;
    QAction *actionUpdate;
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuQuery;
    QMenu *menuHelp;
    QMenu *menuOpetion;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(710, 675);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/scissors.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/power-off.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionConditionQuery = new QAction(MainWindow);
        actionConditionQuery->setObjectName(QString::fromUtf8("actionConditionQuery"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConditionQuery->setIcon(icon3);
        actionAllQuery = new QAction(MainWindow);
        actionAllQuery->setObjectName(QString::fromUtf8("actionAllQuery"));
        actionAllQuery->setIcon(icon3);
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon4);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon5);
        actionUpdate = new QAction(MainWindow);
        actionUpdate->setObjectName(QString::fromUtf8("actionUpdate"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/update.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdate->setIcon(icon6);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 81, 21));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 70, 691, 541));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 710, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuQuery = new QMenu(menubar);
        menuQuery->setObjectName(QString::fromUtf8("menuQuery"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuOpetion = new QMenu(menubar);
        menuOpetion->setObjectName(QString::fromUtf8("menuOpetion"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuQuery->menuAction());
        menubar->addAction(menuOpetion->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menu->addAction(actionStart);
        menu->addAction(actionStop);
        menu->addAction(actionExit);
        menuQuery->addAction(actionConditionQuery);
        menuQuery->addAction(actionAllQuery);
        menuHelp->addAction(actionShow);
        menuHelp->addAction(actionAbout);
        menuOpetion->addAction(actionAdd);
        menuOpetion->addAction(actionDelete);
        menuOpetion->addAction(actionUpdate);
        toolBar->addAction(actionStart);
        toolBar->addAction(actionExit);
        toolBar->addAction(actionConditionQuery);
        toolBar->addAction(actionAllQuery);
        toolBar->addAction(actionAdd);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionUpdate);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
        actionStop->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\234\215\345\212\241\345\231\250", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionConditionQuery->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\347\211\271\345\256\232\350\210\252\347\217\255", nullptr));
        actionAllQuery->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\346\211\200\346\234\211\350\210\252\347\217\255", nullptr));
        actionShow->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\206\205\345\256\271", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        actionAdd->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\350\210\252\347\217\255\344\277\241\346\201\257", nullptr));
        actionDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\210\252\347\217\255\344\277\241\346\201\257", nullptr));
        actionUpdate->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260\350\210\252\347\217\255\344\277\241\346\201\257", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\347\253\257\346\266\210\346\201\257\357\274\232", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\223\215\344\275\234", nullptr));
        menuQuery->setTitle(QApplication::translate("MainWindow", "\346\234\272\347\245\250\346\237\245\350\257\242", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menuOpetion->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

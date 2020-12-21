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
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(710, 600);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 81, 21));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 40, 691, 471));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 710, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionStart);
        menu->addAction(actionStop);
        menu->addAction(actionExit);
        menu_2->addAction(actionConditionQuery);
        menu_2->addAction(actionAllQuery);
        menu_3->addAction(actionShow);
        menu_3->addAction(actionAbout);
        toolBar->addAction(actionStart);
        toolBar->addAction(actionStop);
        toolBar->addAction(actionExit);
        toolBar->addAction(actionConditionQuery);
        toolBar->addAction(actionAllQuery);

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
        label->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\347\253\257\346\266\210\346\201\257\357\274\232", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\223\215\344\275\234", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\234\272\347\245\250\346\237\245\350\257\242", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

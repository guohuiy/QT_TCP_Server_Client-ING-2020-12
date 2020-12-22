/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QString::fromUtf8("Welcome"));
        Welcome->resize(433, 471);
        pushButton = new QPushButton(Welcome);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 440, 93, 28));
        label = new QLabel(Welcome);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 0, 191, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(28);
        label->setFont(font);
        label_2 = new QLabel(Welcome);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 411, 371));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/cover.png")));

        retranslateUi(Welcome);

        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QWidget *Welcome)
    {
        Welcome->setWindowTitle(QApplication::translate("Welcome", "Form", nullptr));
        pushButton->setText(QApplication::translate("Welcome", "PushButton", nullptr));
        label->setText(QApplication::translate("Welcome", "\346\231\272\346\205\247\345\207\272\350\241\214", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H

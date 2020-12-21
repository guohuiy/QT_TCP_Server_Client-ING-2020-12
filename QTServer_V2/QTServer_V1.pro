QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basethread.cpp \
    infomation.cpp \
    infoprocess.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    threadoperation.cpp \
    threadpool.cpp \
    threadservice.cpp \
    ticket.cpp \
    ticketoperation.cpp

HEADERS += \
    basethread.h \
    gloabalAPI.h \
    infomation.h \
    infoprocess.h \
    mainwindow.h \
    message.h \
    threadoperation.h \
    threadpool.h \
    threadservice.h \
    ticket.h \
    ticketoperation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

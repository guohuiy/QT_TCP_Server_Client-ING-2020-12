#ifndef INFOPROCESS_H
#define INFOPROCESS_H

#include <QObject>
#include <QMutex>
#include "infomation.h"

class InfoProcess : public QObject
{
    Q_OBJECT
public:
    const int static INFO_NUM=10;

    explicit InfoProcess(QObject *parent = nullptr);
    ~InfoProcess();

    void initInfo();
    int getFreeInfo();
    void freeInfo(int index);
    void addInfo(const QString &src);

    bool indexInfoIsOccupied(int index);//指定Infomatio是否被占用，占用返回true,否则false
    QString getIndexOccupiedInfoMsg(int index);//指定Infomation,返回它的message

    void setInfoLock();
    void setInfoUnlock();

private:
    QMutex infoMutex;

    Infomation* info;

signals:

};

#endif // INFOPROCESS_H

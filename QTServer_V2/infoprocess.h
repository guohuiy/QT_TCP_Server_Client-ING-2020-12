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

    int getFreeInfo();
    void freeInfo(int index);
    bool addInfo(const QString &src);
    void inforsOutput(QVector<QString>& msg);

    QString getIndexOccupiedInfoMsg(int index);//指定Infomation,返回它的message

    void setInfoLock();
    void setInfoUnlock();

private:
    QMutex infoMutex;

    QList<Infomation*> info;

signals:

};

#endif // INFOPROCESS_H

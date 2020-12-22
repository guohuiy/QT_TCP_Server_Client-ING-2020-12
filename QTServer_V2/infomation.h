#ifndef INFOMATION_H
#define INFOMATION_H

#include <QObject>
#include "gloabalAPI.h"

class Infomation : public QObject
{
    Q_OBJECT
public:
    /* 提示信息输出 */
    enum {INFO_FREED,INFO_OCCUPIED};

    explicit Infomation(QObject *parent = nullptr);

    int getStatus();
    void setStatus(int status);
    QString getMessage();
    void setMessage(const QString &message);
private:
    QString message;

signals:

};

#endif // INFOMATION_H

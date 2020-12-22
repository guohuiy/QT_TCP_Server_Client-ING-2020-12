#ifndef INFOPROCESSOR_H
#define INFOPROCESSOR_H

#include "information.h"
#include <QObject>
#include <QMutex>

class InfoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit InfoProcessor(QObject *parent = nullptr);
    ~InfoProcessor();
    bool freeInfo(const int index);
    void addInfo(const QString& src);
private:
    QMutex mutex;
    QList<Information*> infoList;
signals:

};

#endif // INFOPROCESSOR_H

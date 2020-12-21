#ifndef THREADOPERATION_H
#define THREADOPERATION_H

#include <QObject>
#include "basethread.h"
#include "ticketoperation.h"
#include "infoprocess.h"
#include <QTcpServer>
#include <QTcpSocket>

class ThreadOperation : public BaseThread
{
    Q_OBJECT
public:
    explicit ThreadOperation(QObject *parent = nullptr);
    ThreadOperation(int buffIndex,int tid,unsigned long ipAddr,int connFd,int buffStatus);
    ~ThreadOperation();

    void dealNewClientMsg(QTcpSocket& client,InfoProcess &infoProcess,TicketOperation& ticketOp);

signals:
    void sendThreadErr(QString s, int index);
};

#endif // THREADOPERATION_H

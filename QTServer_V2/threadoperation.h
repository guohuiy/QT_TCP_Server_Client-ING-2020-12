#ifndef THREADOPERATION_H
#define THREADOPERATION_H

#include <QObject>
#include "message.h"
#include "ticketoperation.h"
#include "infoprocess.h"
#include <QTcpServer>
#include <QTcpSocket>

class ThreadOperation : public QObject
{
    Q_OBJECT
public:
    explicit ThreadOperation(QObject *parent = nullptr);
    ThreadOperation(int buffIndex,int tid,unsigned long ipAddr,int connFd,int buffStatus);
    ~ThreadOperation();

    void dealNewClientMsg(QTcpSocket& client,InfoProcess &infoProcess,TicketOperation& ticketOp);
    int getTid() const;
    void setTid(int value);

    unsigned long getIpAddr() const;
    void setIpAddr(unsigned long value);

    int getConnFd() const;
    void setConnFd(int value);

private:
    Config* config;
    bool start;
    int tid;            // 保存对应线程的线程号
    unsigned long ipAddr;  // 保存对应的客户机的IP地址
    int	connFd;        // 该线程使用的连接套接字描述符
signals:
    void sendThreadErr(QString s, int tid);
};

#endif // THREADOPERATION_H

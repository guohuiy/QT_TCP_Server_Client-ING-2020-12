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
    ThreadOperation(int tid,unsigned long ipAddr,int connFd);
    ~ThreadOperation();

    void dealNewClientMsg(QTcpSocket *client,InfoProcess *infoProcess,TicketOperation *ticketOp);
    void listenThread();
    void writeErr(unsigned int errMsg);
    int getTid() const;
    void setTid(int value);

    unsigned long getIpAddr() const;
    void setIpAddr(unsigned long value);

    int getConnFd() const;
    void setConnFd(int value);

    void setMyClient(QTcpSocket *value);

private:
    Config* config;
    QTcpServer* myServer;
    QTcpSocket* myClient;
    Message *message;

    int tid;            // 保存对应线程的线程号
    unsigned long ipAddr;  // 保存对应的客户机的IP地址
    int	connFd;        // 该线程使用的连接套接字描述符
signals:
    void sendOver(QString msg);
    void reciveMessage(QTcpSocket* client, Message *message,int tid);
};

#endif // THREADOPERATION_H

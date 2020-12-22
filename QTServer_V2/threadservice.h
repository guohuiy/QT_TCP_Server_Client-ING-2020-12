#ifndef THREADSERVICE_H
#define THREADSERVICE_H

#include <QObject>
#include "threadpool.h"
#include "threadoperation.h"

class ThreadService : public QObject
{
    Q_OBJECT
public:
    explicit ThreadService(QObject *parent = nullptr);
    ~ThreadService();

    bool listenThread();
    void incomingClientToThreadPool();
    void dealNewConn();
    void serviceStop();
    void serviceExit();
    bool searchFlightInfo(int value,QString& flightMsg);
    bool searchAllFlight(QList<QString> &ticketListMsg);
    bool updateFlightMessage(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice);
    bool deleteFlightMessage(unsigned int flightID);
    bool addFlightMessage(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice);
    void servicePaintEvent(QVector<QString>& msg);
    void threadErr(QString s, int index);
    void serviceThread(Message &message);
    bool isOffline(QTcpSocket &client);

public slots:
    void dealNewMsg();//和业务线程交互专用槽函数
private:
    Config* config;
    bool flag;//标记是否停止监听新用户
    ThreadPool* threadPool;
    QMutex threadPoolMutex;//threadPool的互斥操作

    QThread* qt;
    ThreadOperation* opThread;

    TicketOperation* ticketOp;
    InfoProcess* infoProcess;
    QTcpServer* mServer;
    QTcpSocket* client;

signals:
    void informOpThreadDealMsg(QTcpSocket &client,InfoProcess &infoProcess,TicketOperation& ticketOp);
};

#endif // THREADSERVICE_H

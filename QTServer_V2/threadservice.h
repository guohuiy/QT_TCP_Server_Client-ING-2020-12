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

    void listenThread();
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

    QTcpSocket *getClient() const;
    void setClient(QTcpSocket *value);

    InfoProcess *getInfoProcess() const;
    void setInfoProcess(InfoProcess *value);

    TicketOperation *getTicketOp() const;
    void setTicketOp(TicketOperation *value);

    void dealNewClientMsg(QTcpSocket *client,Message *message,int tid);
public slots:
//    void dealNewMsg(Message *message);//和业务线程交互专用槽函数
    //void dealNewOverMsg(QString msg);
private:
    Config* config;
    bool flag;//标记是否停止监听新用户
    ThreadPool* threadPool;
    QMutex threadPoolMutex;//threadPool的互斥操作
    Message *message;

    QThread* qt;
    ThreadOperation* opThread;

    TicketOperation* ticketOp;
    InfoProcess* infoProcess;
    QTcpServer* mServer;
    QList<QTcpSocket*> clientList;

signals:
    void informOpThreadDealMsg();
    void tellMainWindowClientOver(QString msg);
};

#endif // THREADSERVICE_H

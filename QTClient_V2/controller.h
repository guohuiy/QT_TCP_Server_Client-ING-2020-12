#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "message.h"
#include <QObject>
#include <QTcpSocket>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void connectServer();
    void isConnect();
    void disconnectServer();
    void exitServer();
    int buyTicket(unsigned int flightID,unsigned int ticketNum);
    void receiveMsg();

    int conditionQuery(unsigned int flightID);
    int allQuery();

private:
    QTcpSocket* client;
    bool connectflag;
signals:
    void sendBuySuccess(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void sendBuyFailure(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void sendQuerySuccess(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void sendQueryFailed(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void sendQueryAllSuccess(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void sendQueryAllFailed(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
};

#endif // CONTROLLER_H

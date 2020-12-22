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
    void sendBuySuccess();
    void sendBuyFailure();
    void sendQuerySuccess();
    void sendQueryFailed();
    void sendQueryAllSuccess();
    void sendQueryAllFailed();
};

#endif // CONTROLLER_H

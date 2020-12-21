#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "gloabalAPI.h"

/*服务器与客户端使用的消息*/
class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    Message(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
    void initMessage();//初始化信息
    unsigned int getMsgType() const;
    void setMsgType(unsigned int value);

    unsigned int getFlightID() const;
    void setFlightID(unsigned int value);

    unsigned int getTicketNum() const;
    void setTicketNum(unsigned int value);

    unsigned int getTicketTotalPrice() const;
    void setTicketTotalPrice(unsigned int value);

private:
    unsigned int msgType;
    unsigned int flightID;              //航班号
    unsigned int ticketNum;             //机票张数
    unsigned int ticketTotalPrice;     //机票价钱

signals:

};

#endif // MESSAGE_H

#ifndef MESSAGE_H
#define MESSAGE_H

#include "msginfo.h"
#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    Message(unsigned int msgType,unsigned int flightID,unsigned int ticketNum,unsigned int ticketTotalPrice);
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
    unsigned int flightID;
    unsigned int ticketNum;
    unsigned int ticketTotalPrice;
signals:

};

#endif // MESSAGE_H

#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{
    msgType=INITIAL_VALUE;
    flightID=0;
    ticketNum=0;
    ticketTotalPrice=0;
}

unsigned int Message::getMsgType() const
{
    return msgType;
}

void Message::setMsgType(unsigned int value)
{
    msgType = value;
}

unsigned int Message::getFlightID() const
{
    return flightID;
}

void Message::setFlightID(unsigned int value)
{
    flightID = value;
}

unsigned int Message::getTicketNum() const
{
    return ticketNum;
}

void Message::setTicketNum(unsigned int value)
{
    ticketNum = value;
}

unsigned int Message::getTicketTotalPrice() const
{
    return ticketTotalPrice;
}

void Message::setTicketTotalPrice(unsigned int value)
{
    ticketTotalPrice = value;
}

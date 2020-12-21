#include "ticket.h"

Ticket::Ticket(QObject *parent) : QObject(parent)
{
    this->flightID=0;
    this->ticketNum=0;
    this->ticketPrice=0;
}

Ticket::Ticket(unsigned int flightID, unsigned int ticketNum, unsigned int ticketPrice)
{
    this->flightID=flightID;
    this->ticketNum=ticketNum;
    this->ticketPrice=ticketPrice;
}

unsigned int Ticket::getFlightId()
{
    return this->flightID;
}

void Ticket::setFlightId(unsigned int flightID)
{
    this->flightID=flightID;
}

unsigned int Ticket::getTicketNum()
{
    return this->ticketNum;
}

void Ticket::setTicketNum(unsigned int ticketNum)
{
    this->ticketNum=ticketNum;
}

unsigned int Ticket::getTicketPrice()
{
    return this->ticketPrice;
}

void Ticket::setTicketPrice(unsigned int ticketPrice)
{
    this->ticketPrice=ticketPrice;
}

void Ticket::setTicketMutexLock()
{
    ticketMutex.lock();
}

void Ticket::setTicketMutexUnlock()
{
    ticketMutex.unlock();
}

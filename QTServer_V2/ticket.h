#ifndef TICKET_H
#define TICKET_H

#include <QObject>
#include <QMutex>

class Ticket : public QObject
{
    Q_OBJECT
public:
    explicit Ticket(QObject *parent = nullptr);
    Ticket(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice);

    unsigned int getFlightId();
    void setFlightId(unsigned int flightID);
    unsigned int getTicketNum();
    void setTicketNum(unsigned int ticketNum);
    unsigned int getTicketPrice();
    void setTicketPrice(unsigned int ticketPrice);

    void setTicketMutexLock();
    void setTicketMutexUnlock();
private:
    unsigned int flightID;
    unsigned int ticketNum;
    unsigned int ticketPrice;	//票价

    /*多个线程操作时，必须对机票的剩余数量进行保护。由于这样的操作比较频繁，所以应当对每一个ticket_num使用不同的互斥锁，否则将对线程间并行性有较大影响。*/
    QMutex	ticketMutex;

signals:

};

#endif // TICKET_H

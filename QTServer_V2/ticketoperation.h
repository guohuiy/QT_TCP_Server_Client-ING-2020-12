#ifndef TICKETOPERATION_H
#define TICKETOPERATION_H

#include <QObject>
#include "ticket.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QList>
#include "message.h"
#include "config.h"

class TicketOperation : public QObject
{
    Q_OBJECT
public:
    explicit TicketOperation(QObject *parent = nullptr);
    ~TicketOperation();

    bool updateDatabase(QString sql);
    bool deleteFlightMsgDatebase(unsigned int flightID);
    bool addFlightMsgDatebase(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice);
    bool updateFlightMsgDatebase(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice);
    bool openDatabase(QSqlDatabase &db);
    void closeDatabase(QSqlDatabase &db);

    /* readTicketList:初始化ticketList数组 */
    void readTicketList();
    bool ticketInfoList(QList<QString>& tL);
    bool searchFlightIdInfoToString(unsigned int flightID,QString &msg);
    bool searchFlightIdInfoToMessage(unsigned int flightID,Message &msg);
    bool searchAllFlight(QVector<Message*> &vMsg);
    bool buyTicket(Message &msg);

    int getNumRows();
    void setNumRows(int numRows);
private:
    const QString database="base";
    const QString hostname="hostname";
    const QString username="username";
    const QString password="password";
    const QString mydatabase="database";

    Config* config;
    int numRows;

    QList<Ticket*> ticketList;
    QMutex dataBaseMutex;
signals:

};

#endif // TICKETOPERATION_H

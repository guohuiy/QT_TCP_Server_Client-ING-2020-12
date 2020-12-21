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
#include "gloabalAPI.h"

class TicketOperation : public QObject
{
    Q_OBJECT
public:
    explicit TicketOperation(QObject *parent = nullptr);
    ~TicketOperation();

    bool updateDatabase(QString sql);
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
    int numRows;

    QList<Ticket*> ticketList;
    QMutex dataBaseMutex;
signals:

};

#endif // TICKETOPERATION_H

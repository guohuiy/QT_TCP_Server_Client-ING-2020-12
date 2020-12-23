#include "controller.h"
#include "msginfo.h"
#include <QHostAddress>
#include <QDataStream>

Controller::Controller(QObject *parent) : QObject(parent)
{
    connectflag=false;
    client=new QTcpSocket(this);

    //收到消息
    connect(client,&QTcpSocket::readyRead,this,&Controller::receiveMsg);
}

Controller::~Controller()
{
    delete client;
}

void Controller::connectServer()
{
    connectflag=false;
    client->connectToHost(QHostAddress("192.168.199.136"),8889);

    connect(client,&QTcpSocket::connected,this,&Controller::isConnect);
}

void Controller::isConnect()
{
    connectflag=true;
}

void Controller::disconnectServer()
{
    client->disconnectFromHost();
    QByteArray bArr;
    QDataStream in(&bArr,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_12);
    in<<DISCONNECT<<0<<0<<0;
}

void Controller::exitServer()
{
    disconnectServer();
}

int Controller::buyTicket(unsigned int flightID,unsigned int ticketNum)
{
    qDebug()<<"buyTicket:::--------------";
    /* 购买机票 */
    Message message(this);
    message.setMsgType(BUY_TICKET);
    message.setFlightID(flightID);
    message.setTicketNum(ticketNum);
    //char buff[1024]={0};
    QByteArray bArr;
    QDataStream in(&bArr,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_12);
    //in<<(quint64)0;
    in<<message.getMsgType()<<message.getFlightID()<<message.getTicketNum()<<message.getTicketTotalPrice();
    //in.device()->seek(0);
    //in<<(quint64)(bArr.size()-sizeof (quint64));
    qDebug()<<bArr;

    return client->write(bArr);
}

void Controller::receiveMsg()
{
    unsigned int msgType;
    unsigned int flightID;
    unsigned int ticketNum;
    unsigned int ticketTotalPrice;
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_12);

    in >> msgType>>flightID>>ticketNum>>ticketTotalPrice;
    qDebug()<<msgType,flightID,ticketNum,ticketTotalPrice;
    if(msgType==BUY_SUCCEED) emit sendBuySuccess(msgType,flightID,ticketNum,ticketTotalPrice);
    else if(msgType==INQUIRE_SUCCEED) emit sendQuerySuccess(msgType,flightID,ticketNum,ticketTotalPrice);
    else if(msgType==BUY_FAILED) emit sendBuyFailure(msgType,flightID,ticketNum,ticketTotalPrice);
    else if(msgType==INQUIRE_FAILED) emit sendQueryFailed(msgType,flightID,ticketNum,ticketTotalPrice);
    else if(msgType==INQUIRE_ALL_FAILED) emit sendQueryAllFailed(msgType,flightID,ticketNum,ticketTotalPrice);
    else if(msgType==INQUIRE_ALL_SUCCEED) emit sendQueryAllSuccess(msgType,flightID,ticketNum,ticketTotalPrice);

}

int Controller::conditionQuery(unsigned int flightID)
{
    QByteArray bArr;
    QDataStream in(&bArr,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_12);
    in<<INQUIRE_ONE<<flightID<<0<<0;
    //in<<(quint64)(bArr.size()-sizeof (quint64));
    return client->write(bArr);
}

int Controller::allQuery()
{
    QByteArray bArr;
    QDataStream in(&bArr,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_12);
    in<<INQUIRE_ALL<<0<<0<<0;

    return client->write(bArr);
}


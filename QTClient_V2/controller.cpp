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
}

void Controller::exitServer()
{
    client->abort();
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
    in<<(quint64)(bArr.size()-sizeof (quint64));
    qDebug()<<bArr;

    return client->write(bArr);
}

void Controller::receiveMsg()
{
    char buff[1024]{0};
    client->read(buff,sizeof buff);
    QByteArray bArr(buff);
    QDataStream out(bArr);
    unsigned int msgType=INITIAL_VALUE;
    out>>msgType;
    if(msgType==BUY_SUCCEED) emit sendBuySuccess();
    else if(msgType==INQUIRE_SUCCEED) emit sendQuerySuccess();
    else if(msgType==BUY_FAILED) emit sendBuyFailure();
    else if(msgType==INQUIRE_FAILED) emit sendQueryFailed();
    else if(msgType==INQUIRE_ALL_FAILED) emit sendQueryAllFailed();
    else if(msgType==INQUIRE_ALL_SUCCEED) emit sendQueryAllSuccess();

}

int Controller::conditionQuery(unsigned int flightID)
{
    char buff[1024]{0};
    client->read(buff,sizeof buff);
    QByteArray bArr(buff);
    QDataStream in(bArr);
    in<<INQUIRE_ONE<<flightID<<0<<0;

    return client->write(buff);
}

int Controller::allQuery()
{
    char buff[1024]{0};
    client->read(buff,sizeof buff);
    QByteArray bArr(buff);
    QDataStream in(bArr);
    in<<INQUIRE_ALL<<0<<0<<0;

    return client->write(buff);
}


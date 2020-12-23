#include "threadoperation.h"
#include <QThread>

ThreadOperation::ThreadOperation(QObject *parent) : QObject(parent)
{
    config=new Config(this);
    myServer=new QTcpServer(this);
    myClient=new QTcpSocket(this);
    message=new Message(this);
    tid=0;
    ipAddr=0;
    connFd=0;
}
ThreadOperation::ThreadOperation(int tid, unsigned long ipAddr, int connFd)
{
    config=new Config(this);
    this->tid=tid;
    this->ipAddr=ipAddr;
    this->connFd=connFd;

}

ThreadOperation::~ThreadOperation()
{
    delete config;
    delete myServer;
    delete myClient;
    delete message;
}

void ThreadOperation::listenThread()
{
    this->setTid(*(int*)QThread::currentThread());
    qDebug()<<"ThreadOperation::listenThread：小线程：：："<<this->getTid();
    if(myServer->listen(QHostAddress(ipAddr),8889))
    {
        //当有客户端成功连接到该服务器线程会触发信号newConnection
        //connect(myServer,&QTcpServer::newConnection,this,[this](){
            //myClient=client;//= myServer->nextPendingConnection();//返回下一个即将连接的套接字
            qDebug()<<"读客户端消息："<<myClient->peerAddress().toIPv4Address();
            connect(myClient,&QTcpSocket::readyRead,this,[this](){
                unsigned int msgType;
                unsigned int flightID;
                unsigned int ticketNum;
                unsigned int ticketTotalPrice;

                QDataStream in(myClient);
                in.setVersion(QDataStream::Qt_5_12);
                in >> msgType>>flightID>>ticketNum>>ticketTotalPrice;
                //Message message(msgType,flightID,ticketNum,ticketTotalPrice);
                message->setMsgType(msgType);
                message->setFlightID(flightID);
                message->setTicketNum(ticketNum);
                message->setTicketTotalPrice(ticketTotalPrice);
                emit reciveMessage(myClient,message,tid);
            });
        //});

    }
}

int ThreadOperation::getTid() const
{
    return tid;
}

void ThreadOperation::setTid(int value)
{
    tid = value;
}

unsigned long ThreadOperation::getIpAddr() const
{
    return ipAddr;
}

void ThreadOperation::setIpAddr(unsigned long value)
{
    ipAddr = value;
}

int ThreadOperation::getConnFd() const
{
    return connFd;
}

void ThreadOperation::setConnFd(int value)
{
    connFd = value;
}

void ThreadOperation::setMyClient(QTcpSocket *value)
{
    myClient = value;
}


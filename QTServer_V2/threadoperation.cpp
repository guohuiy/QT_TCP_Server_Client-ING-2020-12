#include "threadoperation.h"
#include <QThread>

ThreadOperation::ThreadOperation(QObject *parent) : QObject(parent)
{
    config=new Config(this);
    tid=0;            // 保存对应线程的线程号
    ipAddr=0;  // 保存对应的客户机的IP地址
    connFd=0;        // 该线程使用的连接套接字描述符
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
}

//bool ThreadOperation::listenThread()
//{
//    bool ret=mServer->listen(*hostAddr,this->getConnFd());
//    if(ret)//服务器监听
//    {
//        //当有客户端成功连接到该服务器线程会触发信号newConnection
//        connect(mServer,&QTcpServer::newConnection,this,&OperationThread::dealNewClientMsg);
//        //connect(this,&MainWindow::newConnComing,this,&MainWindow::incomingClientToThreadPool);
//    }

//    return ret;
//}


void ThreadOperation::dealNewClientMsg(QTcpSocket *client,InfoProcess *infoProcess,TicketOperation *ticketOp)
{

    this->setTid(*(int*)QThread::currentThread());
    qDebug()<<"dealNewClientMsg::线程"<<this->getTid();
    QString msg=QString("客户端新消息-->线程ID：%1, 连接ID：%2, 远端地址：%3, 端口号：%4\n").arg(
                this->getTid()).arg(this->getConnFd()).arg(client->peerAddress().toString()).arg(client->peerPort());
    infoProcess->addInfo(msg);

    unsigned int msgType;
    unsigned int flightID;
    unsigned int ticketNum;
    unsigned int ticketTotalPrice;

//    char str[1024]={0};
//    int msgRet=client->read(str,sizeof str);
//    QByteArray ba(str);
//    //qDebug()<<"服务器：：："<<ba;
//    QDataStream in(&ba,QIODevice::ReadWrite);
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_12);

    in >> msgType>>flightID>>ticketNum>>ticketTotalPrice;
    Message message(msgType,flightID,ticketNum,ticketTotalPrice);

    qDebug()<<"dealNewClientMsg：航班："<<flightID;
    qDebug()<<msgType<<flightID<<ticketNum<<ticketTotalPrice;

    int msgRet=0;
//    /* 接收出错 */
//    if(msgRet==-1)
//    {
//        qDebug()<<"dealNewClientMsg：消息读取错误";
//        msg=QString("线程：%d 在连接：%d 接收出错。连接将关闭。\n").arg((unsigned short)this->getTid(), this->getConnFd());
//        infoProcess->addInfo(msg);
//        emit sendThreadErr(msg, this->getTid());
//    }
//    else if(msgRet==0)
//    {
//        qDebug()<<"dealNewClientMsg：客户端关闭";
//        msg=QString("线程  %d  的连接( ID：%d ) 客户端已关闭。服务器端连接也将关闭。\n").arg(this->getTid(),this->getConnFd());
//        infoProcess->addInfo(msg);
//        emit sendThreadErr(msg, this->getTid());
//    }
    qDebug()<<msgType<<flightID<<ticketNum<<ticketTotalPrice;
    switch(message.getMsgType())
    {
        case DISCONNECT:
        qDebug()<<"dealNewClientMsg::DISCONNECT";
            msg=QString("线程 %1  的连接(ID： %2 ) 客户端已关闭。服务器端连接也将关闭。\n").arg(this->getTid()).arg(this->getConnFd());
            infoProcess->addInfo(msg);
            emit sendThreadErr(msg, this->getTid());
            break;

        case BUY_TICKET :
        qDebug()<<"dealNewClientMsg::BUY_TICKET";
            ticketOp->readTicketList();
            if(ticketOp->buyTicket(message))
            {
                msg=QString("客户端 %1 购买机票成功！航班号：%2, 票数：%3, 总票价：%4\n").arg(client->peerAddress().toString()).arg(
                                                                         message.getFlightID()).arg(message.getTicketNum(),
                                                                         message.getTicketTotalPrice());

                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message.getMsgType()<<message.getFlightID()<<message.getTicketNum()<<message.getTicketTotalPrice();
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgType= client->write(bArr);

                if(msgRet<0)
                {
                    emit sendThreadErr("购票发送数据异常\n", this->getTid());
                }
            }
            else
            {
                message.setMsgType(BUY_FAILED);
                msg=(QString("客户端 %1 购买机票失败！航班号：%2, 票数：%3, 总票价：%4\n")).arg(client->peerAddress().toString()).arg(
                                                                         message.getFlightID(),
                                                                         message.getTicketNum(),
                                                                         message.getTicketTotalPrice());

                infoProcess->addInfo(msg);
                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message.getMsgType()<<message.getFlightID()<<message.getTicketNum()<<message.getTicketTotalPrice();
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgType= client->write(bArr);

                if(msgRet<0)
                {
                    emit sendThreadErr("购票发送数据出错\n", this->getTid());
                }

            }

            break;

        case INQUIRE_ONE:
        {
            qDebug()<<"dealNewClientMsg::INQUIRE_ONE";
            ticketOp->readTicketList();

            if(ticketOp->searchFlightIdInfoToMessage(message.getFlightID(),message))
            {
                message.setMsgType(INQUIRE_SUCCEED);
                msg=QString("客户端 %s 查询航班号：%d 成功！\n").arg(client->peerAddress().toString()).arg(message.getFlightID());
                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message.getMsgType()<<message.getFlightID()<<message.getTicketNum()<<message.getTicketTotalPrice();
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgType= client->write(bArr);

                if(msgRet<0)
                {
                    emit sendThreadErr("查询发送数据出错\n", this->getTid());
                }
            }
            else
            {
                message.setMsgType(INQUIRE_FAILED);
                msg=QString("客户端 %s 查询航班号：%d 异常！\n").arg(client->peerAddress().toString()).arg(message.getFlightID());
                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message.getMsgType()<<message.getFlightID()<<0<<0;
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgType= client->write(bArr);
                if(msgRet<0)
                {
                    emit sendThreadErr("查询发送数据出错\n", this->getTid());
                }
            }

            break;
        }
        case INQUIRE_ALL:
        {
        qDebug()<<"dealNewClientMsg::INQUIRE_ALL";
            QVector<Message*> vMsg;
            if(ticketOp->searchAllFlight(vMsg))
            {
                msg=QString("客户端 %1 查询所有航班号成功！\n").arg(client->peerAddress().toIPv4Address());
                infoProcess->addInfo(msg);

                foreach(Message* m,vMsg)
                {
                    m->setMsgType(INQUIRE_ALL_SUCCEED);
                    QByteArray bArr;
                    QDataStream in(&bArr,QIODevice::ReadWrite);
                    in.setVersion(QDataStream::Qt_5_12);
                    in<<m->getMsgType()<<m->getFlightID()<<m->getTicketNum()<<m->getTicketTotalPrice();

                    msgType= client->write(bArr);
                    delete m;
                    if(msgRet<0)
                    {
                        emit sendThreadErr("查询发送数据出错\n", this->getTid());
                    }
                }
            }
            else
            {
                msg=QString("客户端 %s 查询所有航班号异常！\n").arg(client->peerAddress().toString());
                infoProcess->addInfo(msg);
                message.setMsgType(INQUIRE_ALL_FAILED);
                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message.getMsgType()<<0<<0<<0;
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgType= client->write(bArr);
                if(msgRet<0)
                {
                    emit sendThreadErr("查询发送数据出错\n", this->getTid());
                }
            }
            break;
        }
        case ADD_TICKET://管理员操作
        qDebug()<<"dealNewClientMsg::ADD_TICKET";
            ticketOp->readTicketList();
            if(ticketOp->updateDatabase(QString("insert into ticket values(%d, %d, %d)").arg(message.getFlightID(),message.getTicketNum(),message.getTicketTotalPrice())))
            {
                msg=QString("插入数据成功！\n");
                infoProcess->addInfo(msg);
            }
            else
            {
                msg=QString("插入数据异常！\n");
                infoProcess->addInfo(msg);
            }
            break;

        case UPDATE_TICKET://管理员操作
        qDebug()<<"dealNewClientMsg::UPDATE_TICKET";
            ticketOp->readTicketList();
            if(ticketOp->updateDatabase(QString("update ticket set ticketPrice = %d where flightID = %d").arg(message.getTicketTotalPrice(),message.getFlightID())))
            {
                msg=QString("修改数据成功！\n");
                infoProcess->addInfo(msg);
            }
            else
            {
                msg=QString("修改数据异常！\n");
                infoProcess->addInfo(msg);
            }
            break;

        case DELETE_TICKET://管理员操作
            ticketOp->readTicketList();
            if(ticketOp->updateDatabase(QString("delete from ticket where flightID = %d").arg(message.getFlightID())))
            {
                msg=QString("删除数据成功！\n");
                infoProcess->addInfo(msg);
            }
            else
            {
                msg=QString("删除数据异常！\n");
                infoProcess->addInfo(msg);
            }

            break;

        default:
            message.setMsgType(UNKNOWN_CODE);
            QByteArray bArr;
            QDataStream in(&bArr,QIODevice::ReadWrite);
            in.setVersion(QDataStream::Qt_5_12);
            in<<message.getMsgType()<<0<<0<<0;
            in<<(quint64)(bArr.size()-sizeof (quint64));
            msgType=client->write(bArr);
            if(msgRet<0)
            {
                emit sendThreadErr("查询发送数据出错\n", this->getTid());
            }

    }

}

void ThreadOperation::writeErr(unsigned int errMsg)
{

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

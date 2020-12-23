#include "threadservice.h"

ThreadService::ThreadService(QObject *parent) : QObject(parent)
{
    flag=false;
    config=new Config(this);
    threadPool=new ThreadPool(this);
    mServer=new QTcpServer(this);
    //下面要消户
    infoProcess=new InfoProcess(this);

    ticketOp=new TicketOperation(this);

    //发送数据到客户端
    message=new Message(this);
}

ThreadService::~ThreadService()
{
    delete config;
    delete infoProcess;
    delete threadPool;
    foreach(auto client,clientList) delete client;
    delete ticketOp;
    delete mServer;
    delete message;
}

//服务器开启监听，收端客户端连接就创建服务器线程
void ThreadService::listenThread()
{

    if(mServer->listen(QHostAddress::Any,8889))
    {
        connect(mServer,&QTcpServer::newConnection,this,&ThreadService::dealNewConn);
        //return true;
    }

    //return false;
}

void ThreadService::dealNewConn()
{
    qDebug()<<"有客户端来连接；\n";
    //接收处理消息
    QTcpSocket* client=new QTcpSocket(this);
    client= mServer->nextPendingConnection();//返回下一个即将连接的套接字
    qDebug()<<"[]DEBUG]ThreadService::dealNewConn"<<client->localAddress().toIPv4Address();
    /* 检测重复连接 */
    int pos=threadPool->checkConnection(client->localAddress().toIPv4Address());
    if(-1!=pos && isOffline(*client))//老客户已失联
    {
        qDebug()<<"老客户重游；\n";
        //检测到已经断开,重新创建服务线程
        infoProcess->addInfo(QString("重复连接：%s，旧连接已经关闭！\n").arg(client->peerAddress().toIPv4Address()));
        threadPool->freeBuff(client->localAddress().toIPv4Address());
        foreach(auto c,clientList)
        {
            if(c->localAddress().toIPv4Address()==client->localAddress().toIPv4Address())
            {
                delete c;break;
            }
        }
        opThread=new ThreadOperation;
        opThread->setMyClient(client);
        qt=new QThread(this);
        //创建服务线程描述信息
        opThread->setIpAddr(client->localAddress().toIPv4Address());
        opThread->setConnFd(client->peerPort());
        opThread->moveToThread(qt);
        threadPool->addThread(opThread,qt);
        clientList.append(client);
        qt->start();
    }
    else if(pos==-1) //新客户
    {
        qDebug()<<"新客户；\n";
        clientList.append(client);
        opThread=new ThreadOperation;
        qt=new QThread(this);
        opThread->setMyClient(client);
        opThread->setIpAddr(client->localAddress().toIPv4Address());
        opThread->setConnFd(client->peerPort());
        opThread->moveToThread(qt);
        threadPool->addThread(opThread,qt);
        qt->start();
    }
    else//老客户
    {
        qDebug()<<"老客户；\n";
        delete client;
        opThread=threadPool->searchThread(pos);
        opThread->setMyClient(client);
        qt=threadPool->searchQThread(pos);
    }

    //服务线程要做的事
    connect(opThread,&ThreadOperation::reciveMessage,this,&ThreadService::dealNewClientMsg);
    connect(this,&ThreadService::informOpThreadDealMsg,opThread,&ThreadOperation::listenThread);
    //connect(client,&QTcpSocket::readyRead,this,&ThreadService::dealNewMsg);
    //connect(opThread,&ThreadOperation::sendOver,this,&ThreadService::dealNewOverMsg);

    emit informOpThreadDealMsg();
    //QHostAddress haddr = client->peerAddress();//获取IP
    //int port = client->peerPort();
    //qDebug()<<QHostAddress("192.168.1.1").toIPv4Address();//int32
    //qDebug()<<QHostAddress(3232235777).toString();//"a.b.b.c"


}

void ThreadService::serviceStop()
{
    mServer->pauseAccepting();
    flag=true;
}

void ThreadService::serviceExit()
{
    serviceStop();
    mServer->close();
}


bool ThreadService::searchFlightInfo(int value,QString& flightMsg)
{
    if(!ticketOp->searchFlightIdInfoToString(value,flightMsg))
    {
        return false;
    }
    return true;
}

bool ThreadService::searchAllFlight(QList<QString> &ticketListMsg)
{
    return ticketOp->ticketInfoList(ticketListMsg);
}

bool ThreadService::updateFlightMessage(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice)
{
    return ticketOp->updateFlightMsgDatebase(flightID,ticketNum,ticketPrice);
}

bool ThreadService::deleteFlightMessage(unsigned int flightID)
{
    return ticketOp->deleteFlightMsgDatebase(flightID);
}

bool ThreadService::addFlightMessage(unsigned int flightID, unsigned int ticketNum, unsigned int ticketPrice)
{
    return ticketOp->addFlightMsgDatebase(flightID,ticketNum,ticketPrice);
}

void ThreadService::servicePaintEvent(QVector<QString>& msg)
{
    infoProcess->inforsOutput(msg);
}

void ThreadService::threadErr(QString s, int tid)
{
    qDebug()<<"线程"<<tid<<"异常";
    QString msg = QString("线程号%1 发生致命错误 %2\n").arg(tid).arg(s);
    infoProcess->addInfo(msg);
    //info_print(strmsg,serverwindow);
    /*释放线程使用的线程缓冲区*/
    threadPool->freeBuff(tid);
}


bool ThreadService::isOffline(QTcpSocket &client)
{
    QByteArray bArr;
    QDataStream in(&bArr,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_12);
    in<<INITIAL_VALUE<<0<<0<<0;
    int retMsg = client.write(bArr);
    if(retMsg == -1)
        return true;
    return false;
}

TicketOperation *ThreadService::getTicketOp() const
{
    return ticketOp;
}

void ThreadService::setTicketOp(TicketOperation *value)
{
    ticketOp = value;
}

InfoProcess *ThreadService::getInfoProcess() const
{
    return infoProcess;
}

void ThreadService::setInfoProcess(InfoProcess *value)
{
    infoProcess = value;
}

//QTcpSocket *ThreadService::getClient() const
//{
//    return client;
//}

//void ThreadService::setClient(QTcpSocket *value)
//{
//    client = value;
//}

void ThreadService::dealNewClientMsg(QTcpSocket *client,Message *message,int tid)//QTcpSocket *client,InfoProcess *infoProcess,TicketOperation *ticketOp
{
//    qDebug()<<"dealNewClientMsg::线程"<<this->getTid();
//    QString msg=QString("客户端新消息-->线程ID：%1, 连接ID：%2, 远端地址：%3, 端口号：%4\n").arg(
//                this->getTid()).arg(this->getConnFd()).arg(client->peerAddress().toString()).arg(client->peerPort());
//    infoProcess->addInfo(msg);

//    unsigned int msgType;
//    unsigned int flightID;
//    unsigned int ticketNum;
//    unsigned int ticketTotalPrice;

//    QDataStream in(client);
//    in.setVersion(QDataStream::Qt_5_12);

//    in >> msgType>>flightID>>ticketNum>>ticketTotalPrice;
//    Message message(msgType,flightID,ticketNum,ticketTotalPrice);

//    qDebug()<<"dealNewClientMsg：航班："<<flightID;
    //qDebug()<<"客户端查询"<<message->getMsgType()<<flightID<<ticketNum<<ticketTotalPrice;
    QString msg;
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
    qDebug()<<message->getMsgType()<<message->getFlightID()<<message->getTicketNum()<<message->getTicketTotalPrice();
    switch(message->getMsgType())
    {
        case DISCONNECT:
        qDebug()<<"dealNewClientMsg::DISCONNECT";
            msg=QString("线程 %1  的连接 客户端已关闭。服务器端连接也将关闭。\n").arg(tid);
            infoProcess->addInfo(msg);
            threadErr(msg,tid);
            break;

        case BUY_TICKET :
        qDebug()<<"dealNewClientMsg::BUY_TICKET";
            ticketOp->readTicketList();
            if(ticketOp->buyTicket(*message))
            {
                msg=QString("客户端 %1 购买机票成功！航班号：%2, 票数：%3, 总票价：%4\n").arg(client->peerAddress().toString()).
                        arg(message->getFlightID()).arg(message->getTicketNum()).arg(message->getTicketTotalPrice());

                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message->getMsgType()<<message->getFlightID()<<message->getTicketNum()<<message->getTicketTotalPrice();
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgRet= client->write(bArr);

                if(msgRet<0)
                {
                    threadErr("购票发送数据出错\n", tid);
                }
            }
            else
            {
                message->setMsgType(BUY_FAILED);
                msg=(QString("客户端 %1 购买机票失败！航班号：%2, 票数：%3, 总票价：%4\n")).arg(client->peerAddress().toString()).arg(
                                                                         message->getFlightID(),
                                                                         message->getTicketNum(),
                                                                         message->getTicketTotalPrice());

                infoProcess->addInfo(msg);
                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message->getMsgType()<<message->getFlightID()<<message->getTicketNum()<<message->getTicketTotalPrice();
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgRet= client->write(bArr);

                if(msgRet<0)
                {
                    threadErr("购票发送数据出错\n", tid);
                }

            }

            break;

        case INQUIRE_ONE:
        {
            qDebug()<<"dealNewClientMsg::INQUIRE_ONE";
            ticketOp->readTicketList();

            if(ticketOp->searchFlightIdInfoToMessage(message->getFlightID(),*message))
            {
                message->setMsgType(INQUIRE_SUCCEED);
                msg=QString("客户端 %1 查询航班号：%2 成功！\n").arg(client->peerAddress().toString()).arg(message->getFlightID());
                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message->getMsgType()<<message->getFlightID()<<message->getTicketNum()<<message->getTicketTotalPrice();
                //in<<(quint64)(bArr.size()-sizeof (quint64));
                msgRet= client->write(bArr);
qDebug()<<"查询到的要发送的信息"<<message->getMsgType()<<message->getFlightID()<<message->getTicketNum()<<message->getTicketTotalPrice();
                if(msgRet<0)
                {
                    threadErr("发送数据出错\n", tid);
                }
            }
            else
            {
                message->setMsgType(INQUIRE_FAILED);
                msg=QString("客户端 %1 查询航班号：%2 异常！\n").arg(client->peerAddress().toString()).arg(message->getFlightID());
                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                in.setVersion(QDataStream::Qt_5_12);
                in<<message->getMsgType()<<message->getFlightID()<<0<<0;
                in<<(quint64)(bArr.size()-sizeof (quint64));
                msgRet= client->write(bArr);
                if(msgRet<0)
                {
                    threadErr("查询发送数据出错\n", tid);
                }
            }

            break;
        }
        case INQUIRE_ALL:
        {
            qDebug()<<"dealNewClientMsg::INQUIRE_ALL";
            if(ticketOp->getNumRows()>0)
            {
                msg=QString("客户端 %1 查询所有航班号成功！\n").arg(client->peerAddress().toIPv4Address());
                infoProcess->addInfo(msg);

                QByteArray bArr;
                QDataStream in(&bArr,QIODevice::ReadWrite);
                for(int i=0;i<ticketOp->getTicketList().length();++i)
                {

                    in.setVersion(QDataStream::Qt_5_12);
                    in<<INQUIRE_ALL_SUCCEED<<ticketOp->getTicketList().at(i)->getFlightId()<<ticketOp->getTicketList().at(i)->getTicketNum()<<ticketOp->getTicketList().at(i)->getTicketPrice();
                    qDebug()<<"查询到的要发送的信息"<<INQUIRE_ALL_SUCCEED<<"票号"<<ticketOp->getTicketList().at(i)->getFlightId()<<"票数"<<ticketOp->getTicketList().at(i)->getTicketNum()<<"票价"<<ticketOp->getTicketList().at(i)->getTicketPrice();
                }
                msgRet= client->write(bArr);

                qDebug()<<"服务器发送消息返回值"<<msgRet;
                if(msgRet<0)
                {
                    threadErr("查询发送数据出错\n", tid);
                }

            }

            break;
        }
        case ADD_TICKET://管理员操作
        qDebug()<<"dealNewClientMsg::ADD_TICKET";
            ticketOp->readTicketList();
            if(ticketOp->updateDatabase(QString("insert into ticket values(%d, %d, %d)").arg(message->getFlightID(),message->getTicketNum(),message->getTicketTotalPrice())))
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
            if(ticketOp->updateDatabase(QString("update ticket set ticketPrice = %d where flightID = %d").arg(message->getTicketTotalPrice(),message->getFlightID())))
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
            if(ticketOp->updateDatabase(QString("delete from ticket where flightID = %d").arg(message->getFlightID())))
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
        {
            message->setMsgType(UNKNOWN_CODE);
            QByteArray bArr;
            QDataStream in(&bArr,QIODevice::ReadWrite);
            in.setVersion(QDataStream::Qt_5_12);
            in<<message->getMsgType()<<0<<0<<0;
            in<<(quint64)(bArr.size()-sizeof (quint64));
            msgRet=client->write(bArr);
            if(msgRet<0)
            {
                threadErr("查询发送数据出错\n", tid);
            }
            break;
        }

    }

}

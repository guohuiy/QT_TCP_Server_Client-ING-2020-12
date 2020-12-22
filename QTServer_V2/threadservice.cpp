#include "threadservice.h"

ThreadService::ThreadService(QObject *parent) : QObject(parent)
{
    flag=false;
    config=new Config(this);
    threadPool=new ThreadPool(this);
    mServer=new QTcpServer(this);
    //下面要消户
    infoProcess=new InfoProcess(this);
    client=new QTcpSocket(this);
    ticketOp=new TicketOperation(this);

}

ThreadService::~ThreadService()
{
    delete config;
    delete infoProcess;
    delete threadPool;
    delete client;
    delete ticketOp;
    delete mServer;
}

//服务器开启监听，收端客户端连接就创建服务器线程
bool ThreadService::listenThread()
{
    bool ret=false;
    if(flag)
    {
        mServer->resumeAccepting();
        flag=false;
        ret=!flag;
    }
    else
    {
        ret=mServer->listen(QHostAddress::Any,8889);
    }


    connect(mServer,&QTcpServer::newConnection,this,&ThreadService::dealNewConn);

    return ret;
}

void ThreadService::incomingClientToThreadPool()
{
    /* 分配线程缓冲区 */
    int threadToolIndex = threadPool->getFreeBuff();
    qDebug()<<threadToolIndex;
    if(threadToolIndex < 0)
    {
        infoProcess->addInfo("没用空闲的线程缓冲区。\n");
    }
    else
    {
        //创建服务线程描述信息
        opThread->setIpAddr(client->localAddress().toIPv4Address());
        opThread->setConnFd(client->peerPort());
        //创建服务线程
        qt=new QThread(this);
        opThread->moveToThread(qt);
        threadPool->addThread(opThread,qt);

        qDebug()<<"incomingClientToThreadPool::::qt->start();";
    }
}

void ThreadService::dealNewConn()
{
    qDebug()<<"有客户端来连接；\n";
    //接收处理消息
    client= mServer->nextPendingConnection();//返回下一个即将连接的套接字
    qDebug()<<client->localAddress().toIPv4Address();
    /* 检测重复连接 */
    int pos=threadPool->checkConnection(client->localAddress().toIPv4Address());
    if(-1!=pos && isOffline(*client))//老客户已失联
    {
        qDebug()<<"老客户重游；\n";
        //检测到已经断开
        infoProcess->addInfo(QString("重复连接：%s，旧连接已经关闭！\n").arg(client->peerAddress().toIPv4Address()));
        threadPool->freeBuff(pos);

        incomingClientToThreadPool();
    }
    else if(pos==-1) //新客户
    {
        qDebug()<<"新客户；\n";
        opThread=new ThreadOperation;
        qt=new QThread(this);
        incomingClientToThreadPool();
    }
    else//老客户
    {
        qDebug()<<"老客户；\n";
        opThread=new ThreadOperation;
        opThread=threadPool->searchThread(pos);
        qt=threadPool->searchQThread(pos);
    }

    //服务线程要做的事
    connect(opThread,&ThreadOperation::sendThreadErr,this,&ThreadService::threadErr);
    connect(this,&ThreadService::informOpThreadDealMsg,opThread,&ThreadOperation::dealNewClientMsg);
    connect(client,&QTcpSocket::readyRead,this,&ThreadService::dealNewMsg);



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
//    threadPoolMutex.lock();

//    //threadPool->~ThreadPool();
//    threadPoolMutex.unlock();

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
    ticketOp->updateFlightMsgDatebase(flightID,ticketNum,ticketPrice);
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
    /*获取空闲的界面输出信息缓冲区，如果没有空闲的,延迟一段时间后继续获取*/
    QString msg = QString("线程号%1 发生致命错误 %2\n").arg(tid).arg(s);
    infoProcess->addInfo(msg);
    //info_print(strmsg,serverwindow);
    /*释放线程使用的线程缓冲区*/
    threadPool->freeBuff(tid);
}


bool ThreadService::isOffline(QTcpSocket &client)
{
    int retMsg = client.write("wake hands");
    if(retMsg == -1)
        return true;
    return false;
}

void ThreadService::dealNewMsg()
{
    if(qt->isRunning()) return ;
    qt->start();
    emit informOpThreadDealMsg(*client,*infoProcess,*ticketOp);
}

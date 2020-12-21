#include "threadservice.h"

ThreadService::ThreadService(QObject *parent) : QObject(parent)
{
    flag=false;
    threadPool=new ThreadPool(this);
    mServer=new QTcpServer(this);
    //下面要消户
    infoProcess=new InfoProcess(this);
    client=new QTcpSocket(this);
    ticketOp=new TicketOperation(this);

}

ThreadService::~ThreadService()
{
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
        ret=mServer->listen(QHostAddress::Any,SERVER_PORT_NO);
    }


    connect(mServer,&QTcpServer::newConnection,this,&ThreadService::dealNewConn);

    return ret;
}

void ThreadService::incomingClientToThreadPool()
{
    /* 分配线程缓冲区 */
    int threadToolIndex = threadPool->getFreeBuff();
    if(threadToolIndex < 0)
    {
        infoProcess->addInfo("没用空闲的线程缓冲区。\n");
        //close(connFd);//断开连接
    }
    else
    {
        threadPoolMutex.lock();
        //创建服务线程描述信息
        opThread->setBuffIndex(threadToolIndex);
        opThread->setIpAddr(client->localAddress().toIPv4Address());
        opThread->setConnFd(client->peerPort());
        opThread->setBuffStatus(1);
        //创建服务线程
        QThread* qt=new QThread(this);
        opThread->moveToThread(qt);
        qt->start();

        opThread->setTid(*(int*)qt->currentThreadId());
        threadPool->addThread(opThread,qt);
        threadPoolMutex.unlock();
    }
}

void ThreadService::dealNewConn()
{
    //接收处理消息
    client= mServer->nextPendingConnection();//返回下一个即将连接的套接字
    /* 检测重复连接 */
    int pos=threadPool->checkConnection(client->localAddress().toIPv4Address());
    if(-1!=pos && isOffline(*client))//老客户已失联
    {
        //检测到已经断开
        infoProcess->addInfo(QString("重复连接：%s，旧连接已经关闭！\n").arg(client->peerAddress().toIPv4Address()));
        threadPoolMutex.lock();
        threadPool->freeBuff(pos);
        threadPoolMutex.unlock();

        incomingClientToThreadPool();
    }
    else if(pos==-1) //新客户
    {
        incomingClientToThreadPool();
    }
    else//老客户
    {
        opThread=threadPool->searchThread(pos);
    }

    //服务线程要做的事
    connect(client,&QTcpSocket::readyRead,this,&ThreadService::dealNewMsg);
    connect(this,&ThreadService::informOpThreadDealMsg,opThread,&ThreadOperation::dealNewClientMsg);

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

void ThreadService::servicePaintEvent(QVector<QString>& msg)
{
    infoProcess->setInfoLock();
    for(int i=0;i<InfoProcess::INFO_NUM;i++)
    {
        if(infoProcess->indexInfoIsOccupied(i))
        {
            msg.append(infoProcess->getIndexOccupiedInfoMsg(i));
            infoProcess->freeInfo(i);
        }
    }
    infoProcess->setInfoUnlock();
}

void ThreadService::threadErr(QString s, int index)
{
    /*获取空闲的界面输出信息缓冲区，如果没有空闲的,延迟一段时间后继续获取*/
    QString msg = QString("线程号%1 发生致命错误 %2\n").arg(threadPool->getIndexThread(index)->getTid()).arg(s);
    infoProcess->addInfo(msg);
    //info_print(strmsg,serverwindow);
    /*释放线程使用的线程缓冲区*/
    threadPoolMutex.lock();
    threadPool->freeBuff(index);
    threadPoolMutex.unlock();
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
    connect(opThread,&ThreadOperation::sendThreadErr,this,&ThreadService::threadErr);
    emit informOpThreadDealMsg(*client,*infoProcess,*ticketOp);
}

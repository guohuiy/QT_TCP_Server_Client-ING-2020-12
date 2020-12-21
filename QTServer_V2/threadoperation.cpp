#include "threadoperation.h"

ThreadOperation::ThreadOperation(QObject *parent) : BaseThread(parent)
{

}
ThreadOperation::ThreadOperation(int buffIndex, int tid, unsigned long ipAddr, int connFd, int buffStatus)
    :BaseThread(buffIndex, tid, ipAddr, connFd, buffStatus)
{

}

ThreadOperation::~ThreadOperation()
{

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


void ThreadOperation::dealNewClientMsg(QTcpSocket& client,InfoProcess &infoProcess,TicketOperation& ticketOp)
{
    //BaseThread* opThread=(BaseThread*)p;
    /*打印远端主机地址*/
    QString msg=QString("新连接-->线程ID：%1, 连接ID：%2, 线程缓冲区索引号：%3, 远端地址：%s, 端口号：%5\n").arg(
                this->getTid()).arg(this->getConnFd()).arg(this->getBuffIndex()).arg(client.peerAddress().toString()).arg(client.peerPort());
    infoProcess.addInfo(msg);

    unsigned int msgType;
    unsigned int flightID;
    unsigned int ticketNum;
    unsigned int ticketTotalPrice;

    char str[1024]={0};
    int msgRet=client.read(str,sizeof str);
    QByteArray ba(str);
    QDataStream in(ba);
    in >> msgType>>flightID>>ticketNum>>ticketTotalPrice;
    Message message(msgType,flightID,ticketNum,ticketTotalPrice);

    /* 接收出错 */
    if(msgRet==-1)
    {
        msg=QString("线程：%d 在连接：%d 接收出错。连接将关闭。\n").arg((unsigned short)this->getTid(), this->getConnFd());
        infoProcess.addInfo(msg);
        emit sendThreadErr(msg, this->getBuffIndex());
    }
    else if(msgRet==0)
    {
        msg=QString("线程  %d  的连接( ID：%d ) 客户端已关闭。服务器端连接也将关闭。\n").arg(this->getTid(),this->getConnFd());
        infoProcess.addInfo(msg);
        emit sendThreadErr(msg, this->getBuffIndex());
    }

    switch(message.getMsgType())
    {
        case DISCONNECT:
            msg=QString("线程 %1  的连接(ID： %2 ) 客户端已关闭。服务器端连接也将关闭。\n").arg(this->getTid()).arg(this->getConnFd());
            infoProcess.addInfo(msg);
            emit sendThreadErr(msg, this->getBuffIndex());
            break;

        case BUY_TICKET :
            ticketOp.readTicketList();
            if(ticketOp.buyTicket(message))
            {
                msg=QString("客户端 %1 购买机票成功！航班号：%2, 票数：%3, 总票价：%4\n").arg(client.peerAddress().toString()).arg(
                                                                         message.getFlightID()).arg(message.getTicketNum(),
                                                                         message.getTicketTotalPrice());

                infoProcess.addInfo(msg);
                msg=QString::number(message.getMsgType())+
                     QString::number(message.getFlightID())+
                     QString::number(message.getTicketNum())+
                     QString::number(message.getTicketTotalPrice());
                msgRet=client.write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));

                if(msgRet<0)
                {
                    emit sendThreadErr("购票发送数据异常\n", this->getBuffIndex());
                }
            }
            else
            {
                message.setMsgType(BUY_FAILED);
                msg=(QString("客户端 %1 购买机票失败！航班号：%2, 票数：%3, 总票价：%4\n")).arg(client.peerAddress().toString()).arg(
                                                                         message.getFlightID(),
                                                                         message.getTicketNum(),
                                                                         message.getTicketTotalPrice());

                infoProcess.addInfo(msg);
                msg=QString::number(message.getMsgType())+
                     QString::number(message.getFlightID())+
                     QString::number(message.getTicketNum())+
                     QString::number(message.getTicketTotalPrice());
                msgRet=client.write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));

                if(msgRet<0)
                {
                    emit sendThreadErr("购票发送数据出错\n", this->getBuffIndex());
                }

            }

            break;

        case INQUIRE_ONE:
        {
            ticketOp.readTicketList();

            if(ticketOp.searchFlightIdInfoToMessage(message.getFlightID(),message))
            {
                message.setMsgType(INQUIRE_SUCCEED);
                msg=QString("客户端 %s 查询航班号：%d 成功！\n").arg(client.peerAddress().toString()).arg(message.getFlightID());
                infoProcess.addInfo(msg);
                msg=QString::number(message.getMsgType())+
                     QString::number(message.getFlightID())+
                     QString::number(message.getTicketNum())+
                     QString::number(message.getTicketTotalPrice());
                msgRet=client.write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));

                if(msgRet<0)
                {
                    emit sendThreadErr("查询发送数据出错\n", this->getBuffIndex());
                }
            }

            break;
        }
        case INQUIRE_ALL:
        {
            ticketOp.readTicketList();
            QVector<Message*> vMsg;
            if(ticketOp.searchAllFlight(vMsg))
            {
                msg=QString("客户端 %s 查询所有航班号成功！\n").arg(client.peerAddress().toString());
                infoProcess.addInfo(msg);

                foreach(Message* m,vMsg)
                {
                    msg=QString::number(m->getMsgType())+
                         QString::number(m->getFlightID())+
                         QString::number(m->getTicketNum())+
                         QString::number(m->getTicketTotalPrice());
                    msgRet=client.write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));
                    delete m;
                    if(msgRet<0)
                    {
                        emit sendThreadErr("查询发送数据出错\n", this->getBuffIndex());
                    }
                }
            }
            else
            {
                msg=QString("客户端 %s 查询所有航班号异常！\n").arg(client.peerAddress().toString());
                infoProcess.addInfo(msg);
            }
            break;
        }
        case ADD_TICKET:
            ticketOp.readTicketList();
            if(ticketOp.updateDatabase(QString("insert into ticket values(%d, %d, %d)").arg(message.getFlightID(),message.getTicketNum(),message.getTicketTotalPrice())))
            {
                msg=QString("插入数据成功！\n");
                infoProcess.addInfo(msg);
            }
            else
            {
                msg=QString("插入数据异常！\n");
                infoProcess.addInfo(msg);
            }
            break;

        case UPDATE_TICKET:
            ticketOp.readTicketList();
            if(ticketOp.updateDatabase(QString("update ticket set ticketPrice = %d where flightID = %d").arg(message.getTicketTotalPrice(),message.getFlightID())))
            {
                msg=QString("修改数据成功！\n");
                infoProcess.addInfo(msg);
            }
            else
            {
                msg=QString("修改数据异常！\n");
                infoProcess.addInfo(msg);
            }
            break;

        case DELETE_TICKET:
            ticketOp.readTicketList();
            if(ticketOp.updateDatabase(QString("delete from ticket where flightID = %d").arg(message.getFlightID())))
            {
                msg=QString("删除数据成功！\n");
                infoProcess.addInfo(msg);
            }
            else
            {
                msg=QString("删除数据异常！\n");
                infoProcess.addInfo(msg);
            }

            break;

        default:
            message.setMsgType(UNKNOWN_CODE);
            msg=QString::number(message.getMsgType())+
                 QString::number(message.getFlightID())+
                 QString::number(message.getTicketNum())+
                 QString::number(message.getTicketTotalPrice());
            msgRet=client.write(msg.toStdString().c_str(),strlen(msg.toStdString().c_str()));

            if(msgRet<0)
            {
                emit sendThreadErr("发送数据出错\n", this->getBuffIndex());
            }
    }
}

#include "ticketoperation.h"

TicketOperation::TicketOperation(QObject *parent) : QObject(parent)
{
    numRows=0;
}

TicketOperation::~TicketOperation()
{
    dataBaseMutex.lock();
    foreach(Ticket* p,ticketList) delete p;
    dataBaseMutex.unlock();
}

bool TicketOperation::updateDatabase(QString sql)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //打开数据库
    if(!openDatabase(db))
    {
        //QMessageBox::warning(this,"错误",db.lastError().text());
        qDebug()<<"readTicketList 打开数据库异常";
        return false;//数据库打开异常
    }
    QSqlQuery query;
    //更新
    query.exec(sql);

    closeDatabase(db);

    return true;
}

bool TicketOperation::openDatabase(QSqlDatabase &db)
{
    //连接数据库
    db.setHostName("localhost");//数据库服务器IP
    db.setUserName("root");//数据库用户名
    db.setPassword("root");//设置密码
    db.setDatabaseName("planeticket");//使用哪个数据库

    return db.open();
}

void TicketOperation::closeDatabase(QSqlDatabase &db)
{
    if(db.isOpen())
        db.close();
    QSqlDatabase::removeDatabase(db.connectionName());
}

/* readTicketList:初始化ticketList数组 */
void TicketOperation::readTicketList()
{
    qDebug()<<"[Debug:]TicketOperation::readTicketList：操作";

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //打开数据库
    if(!openDatabase(db))
    {
        //QMessageBox::warning(this,"错误",db.lastError().text());
        qDebug()<<"readTicketList 打开数据库异常";
        return;//数据库打开异常
    }


    dataBaseMutex.lock();
    foreach(Ticket* t,ticketList) delete t;
    ticketList.clear();
    dataBaseMutex.unlock();

    QSqlQuery query;
    //查询
    query.exec("select * from ticket");
    numRows=query.size();//返回查询结果的行数
    dataBaseMutex.lock();
    while(query.next())//表的下一条的指针
    {
        //取出当前行内容
        qDebug()<< query.value(0).toInt()  //0是第0列
                << query.value(1).toString() //1列
                << query.value(2).toString()
                << query.value("ticketPrice").toInt();

        ticketList.append(new Ticket(query.value("flightID").toInt(),query.value("ticketNum").toInt(),query.value("ticketPrice").toInt()));

    }
    dataBaseMutex.unlock();

    closeDatabase(db);
}

bool TicketOperation::ticketInfoList(QList<QString> &tL)
{

    this->readTicketList();

    dataBaseMutex.lock();
    foreach(Ticket* t,ticketList)
    {
        tL.append(QString("你查询的航班号是：%1, 剩余票数：%2,票价：%3\n").arg(t->getFlightId()).arg(
                      t->getTicketNum()).arg(t->getTicketPrice()));
    }

    if(tL.length()!=numRows)
    {
        dataBaseMutex.unlock();
        return false;
    }
    dataBaseMutex.unlock();
    return true;
}

bool TicketOperation::searchFlightIdInfoToString(unsigned int flightID, QString &msg)
{
    if(flightID<=0 )return false;
    this->readTicketList();

    dataBaseMutex.lock();
    for(int i=0;i<numRows;i++)
    {
        if(ticketList.at(i)->getFlightId()==flightID)
        {
            msg=QString("你查询的航班号是：%1, 剩余票数：%2,票价：%3\n").arg(ticketList.at(i)->getFlightId()).arg(
                    ticketList.at(i)->getTicketNum()).arg(ticketList.at(i)->getTicketPrice());
            dataBaseMutex.unlock();
            return true;
        }

    }
    dataBaseMutex.unlock();
    return false;
}

bool TicketOperation::searchFlightIdInfoToMessage(unsigned int flightID, Message &msg)
{
    if(flightID<=0)return false;
    this->readTicketList();

    dataBaseMutex.lock();
    for(int i=0;i<numRows;i++)
    {
        if(ticketList.at(i)->getFlightId()==flightID)
        {
            msg.setFlightID(ticketList.at(i)->getFlightId());
            msg.setTicketNum(ticketList.at(i)->getTicketNum());
            msg.setTicketTotalPrice(ticketList.at(i)->getTicketPrice());
            dataBaseMutex.unlock();
            return true;
        }

    }
    dataBaseMutex.unlock();
    return false;
}

bool TicketOperation::searchAllFlight(QVector<Message*> &vMsg)
{
    this->readTicketList();

    dataBaseMutex.lock();
    for(int i=0;i<numRows;i++)
    {
        vMsg.push_back(new Message(INQUIRE_SUCCEED,ticketList.at(i)->getFlightId(),ticketList.at(i)->getTicketNum(),ticketList.at(i)->getTicketPrice()));
    }
    if(vMsg.length()==numRows)
    {
        dataBaseMutex.unlock();
        return true;
    }
    dataBaseMutex.unlock();
    return false;
}

bool TicketOperation::buyTicket(Message& msg)
{
    if(msg.getFlightID()<=0 || msg.getFlightID()>(unsigned int)numRows)return false;

    dataBaseMutex.lock();
    for(int i=0;i<numRows;i++)
    {
        if(msg.getFlightID()==ticketList.at(i)->getFlightId())
        {
            if(msg.getTicketNum()<=ticketList.at(i)->getTicketNum())
            {
                //满足条件，出票
                msg.setMsgType(BUY_SUCCEED);
                msg.setTicketTotalPrice(msg.getTicketNum()*ticketList.at(i)->getTicketPrice());
                ticketList.at(i)->setTicketNum(ticketList.at(i)->getTicketNum()-msg.getTicketNum());
                //刷新数据库
                this->updateDatabase(QString("update ticket set ticketNum = %d where flightID = %d").arg(ticketList.at(i)->getTicketNum(),ticketList.at(i)->getFlightId()));
                dataBaseMutex.unlock();
                return true;
            }

        }

    }
    dataBaseMutex.unlock();
    return false;
}


int TicketOperation::getNumRows()
{
    return numRows;
}


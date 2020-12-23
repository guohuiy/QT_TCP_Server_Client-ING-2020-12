#include "ticketoperation.h"

TicketOperation::TicketOperation(QObject *parent) : QObject(parent)
{
    numRows=0;
    config=new Config(this);
}

TicketOperation::~TicketOperation()
{
    delete config;
    dataBaseMutex.lock();
    foreach(Ticket* p,ticketList) delete p;
    dataBaseMutex.unlock();
}

bool TicketOperation::updateDatabase(QString sql)
{
    QSqlDatabase db=QSqlDatabase::addDatabase(config->readConfig(database).toString());
    //打开数据库
    if(!openDatabase(db))
    {
        //QMessageBox::warning(this,"错误",db.lastError().text());
        qDebug()<<"updateDatabase 打开数据库异常";
        return false;//数据库打开异常
    }
    QSqlQuery query;
    //更新
    int ret = query.exec(sql);

    closeDatabase(db);

    return ret;
}

bool TicketOperation::deleteFlightMsgDatebase(unsigned int flightID)
{
    QSqlDatabase db=QSqlDatabase::addDatabase(config->readConfig(database).toString());
    //打开数据库
    if(!openDatabase(db))
    {
        //QMessageBox::warning(this,"错误",db.lastError().text());
        qDebug()<<"deleteFlightMsgDatebase 打开数据库异常:"+db.lastError().text();
        return false;//数据库打开异常
    }
    QSqlQuery query;
    //更新
    int ret = query.exec(QString("delete from ticket  where flightID = %1;").arg(flightID));

    closeDatabase(db);

    return ret;
}

bool TicketOperation::addFlightMsgDatebase(unsigned int flightID,unsigned int ticketNum,unsigned int ticketPrice)
{
    QSqlDatabase db=QSqlDatabase::addDatabase(config->readConfig(database).toString());
    //打开数据库
    if(!openDatabase(db))
    {
        qDebug()<<"addFlightMsgDatebase 打开数据库异常:"+db.lastError().text();
        return false;//数据库打开异常
    }
    QSqlQuery query;
    //更新
    int ret = query.exec(QString("insert into ticket(flightID,ticketNum,ticketPrice) value(%1,%2,%3);").arg(flightID).arg(ticketNum).arg(ticketPrice));

    closeDatabase(db);

    return ret;
}

bool TicketOperation::updateFlightMsgDatebase(unsigned int flightID, unsigned int ticketNum, unsigned int ticketPrice)
{
    QSqlDatabase db=QSqlDatabase::addDatabase(config->readConfig(database).toString());
    //打开数据库
    if(!openDatabase(db))
    {
        qDebug()<<"updateFlightMsgDatebase 打开数据库异常:"+db.lastError().text();
        return false;//数据库打开异常
    }
    QSqlQuery query;
    //更新
    int ret = query.exec(QString("update ticket set ticketNum = %1 ,ticketPrice = &2 where flightID = %3;").arg(ticketNum).arg(ticketPrice).arg(flightID));

    closeDatabase(db);

    return ret;
}

bool TicketOperation::openDatabase(QSqlDatabase &db)
{
    //连接数据库
    db.setHostName(config->readConfig(hostname).toString());//数据库服务器IP
    db.setUserName(config->readConfig(username).toString());//数据库用户名
    db.setPassword(config->readConfig(password).toString());//设置密码
    db.setDatabaseName(config->readConfig(mydatabase).toString());//使用哪个数据库

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
    QSqlDatabase db=QSqlDatabase::addDatabase(config->readConfig(database).toString());
    //打开数据库
    if(!openDatabase(db))
    {
        //QMessageBox::warning(this,"错误",db.lastError().text());
        qDebug()<<"[Debug]readTicketList 打开数据库异常";
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
    for(int i=0;i<ticketList.length();i++)
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
    for(int i=0;i<ticketList.length();i++)
    {
        qDebug()<<"TicketOperation::searchAllFlight:::"<<config->readConfig("INQUIRE_ALL_SUCCEED").toInt();
        vMsg.push_back(new Message(config->readConfig("INQUIRE_ALL_SUCCEED").toInt(),ticketList.at(i)->getFlightId(),ticketList.at(i)->getTicketNum(),ticketList.at(i)->getTicketPrice()));
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
    if(msg.getFlightID()<=0)return false;

    dataBaseMutex.lock();
    for(int i=0;i<numRows;i++)
    {
        if(msg.getFlightID()==ticketList.at(i)->getFlightId())
        {
            if(msg.getTicketNum()<=ticketList.at(i)->getTicketNum())
            {
                //满足条件，出票
                msg.setMsgType(config->readConfig("BUY_SUCCEED").toInt());
                msg.setTicketTotalPrice(msg.getTicketNum()*(ticketList.at(i)->getTicketPrice()));
                ticketList.at(i)->setTicketNum(ticketList.at(i)->getTicketNum()-msg.getTicketNum());
                //刷新数据库
                this->updateDatabase(QString("update ticket set ticketNum = %1 where flightID = %2").arg(ticketList.at(i)->getTicketNum()).arg(ticketList.at(i)->getFlightId()));
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
    readTicketList();
    return numRows;
}

QList<Ticket *> TicketOperation::getTicketList() const
{
    return ticketList;
}


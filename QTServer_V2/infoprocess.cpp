#include "infoprocess.h"
#include <QVector>

InfoProcess::InfoProcess(QObject *parent) : QObject(parent)
{

}

InfoProcess::~InfoProcess()
{

}

int InfoProcess::getFreeInfo()
{
    infoMutex.lock();
    if(info.length()<INFO_NUM) return info.length();
    infoMutex.unlock();
    return -1;
}

void InfoProcess::freeInfo(int index)
{
    setInfoLock();
    Infomation* p=info.at(index);
    info.removeAt(index);
    delete p;
    setInfoUnlock();
}

bool InfoProcess::addInfo(const QString &src)
{
    /* 添加消息 */

    if(info.length()<INFO_NUM)
    {
        setInfoLock();
        Infomation* inf=new Infomation(this);
        inf->setMessage(src);
        info.append(inf);
        setInfoUnlock();
        return true;
    }
    else
    {
        return false;
    }

}

void InfoProcess::inforsOutput(QVector<QString> &msg)
{
    setInfoLock();
    foreach(Infomation* v,info)
    {
        msg.push_back(v->getMessage());
    }
    setInfoUnlock();
}


QString InfoProcess::getIndexOccupiedInfoMsg(int index)
{
    return info.at(index)->getMessage();
}

void InfoProcess::setInfoLock()
{
    infoMutex.lock();
}

void InfoProcess::setInfoUnlock()
{
    infoMutex.unlock();
}

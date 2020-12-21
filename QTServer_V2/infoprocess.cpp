#include "infoprocess.h"

InfoProcess::InfoProcess(QObject *parent) : QObject(parent)
{
    info=new Infomation[InfoProcess::INFO_NUM];
}

InfoProcess::~InfoProcess()
{
    delete[] info;
}

void InfoProcess::initInfo()
{
    infoMutex.lock();
    for(int pos=InfoProcess::INFO_NUM;pos>0;pos--)
    {
        info[pos-1].setStatus(Infomation::INFO_FREED);
        info[pos-1].setMessage("");
    }
    infoMutex.unlock();

}

int InfoProcess::getFreeInfo()
{
    int pos = 0;

    infoMutex.lock();
    for(pos=0;pos<InfoProcess::INFO_NUM; pos++)
    {
        if(info[pos].getStatus()==Infomation::INFO_FREED)
        {
            infoMutex.unlock();
            return pos;
        }
    }

    infoMutex.unlock();
    return -1;
}

void InfoProcess::freeInfo(int index)
{
    setInfoLock();
    if(info[index].getStatus()==info[index].INFO_OCCUPIED)
    {
        info[index].setStatus(info[index].INFO_FREED);
        info[index].setMessage("");
    }
    setInfoUnlock();
}

void InfoProcess::addInfo(const QString &src)
{
    int pos=0;
    while((pos=this->getFreeInfo())==-1)
    {
        _sleep(1);
    }
    /* 添加消息 */
    setInfoLock();
    info[pos].setStatus(info[pos].INFO_OCCUPIED);
    info[pos].setMessage(src);
    setInfoUnlock();
}

bool InfoProcess::indexInfoIsOccupied(int index)
{
    return info[index].getStatus()==info[index].INFO_OCCUPIED;
}

QString InfoProcess::getIndexOccupiedInfoMsg(int index)
{
    return info[index].getMessage();
}

void InfoProcess::setInfoLock()
{
    infoMutex.lock();
}

void InfoProcess::setInfoUnlock()
{
    infoMutex.unlock();
}

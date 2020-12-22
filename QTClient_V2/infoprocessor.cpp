#include "infoprocessor.h"

InfoProcessor::InfoProcessor(QObject *parent) : QObject(parent)
{

}

InfoProcessor::~InfoProcessor()
{
    foreach(auto info,infoList) delete info;
    infoList.clear();
}

bool InfoProcessor::freeInfo(const int index)
{
    mutex.lock();
    if(index>=0 && index <infoList.length())
    {
        Information* p=infoList.at(index);
        infoList.removeAt(index);
        delete p;
        mutex.unlock();
        return true;
    }
    else
    {
        mutex.unlock();
        return false;
    }

}

void InfoProcessor::addInfo(const QString &src)
{
    mutex.lock();
    Information* info=new Information;
    info->setInfo(src);
    infoList.append(info);
    mutex.unlock();
}

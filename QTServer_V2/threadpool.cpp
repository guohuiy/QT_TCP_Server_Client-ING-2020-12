#include "threadpool.h"

ThreadPool::ThreadPool(QObject *parent) : QObject(parent)
{
    info=new InfoProcess(this);
}

ThreadPool::~ThreadPool()
{
    buffMutex.lock();
    foreach(auto p,threadBuff) delete p;
    foreach(auto p,qThreadList)
    {
        exitThread(p);
        delete p;
    }
    buffMutex.unlock();
    delete info;
}

int ThreadPool::getFreeBuff()
{
    qDebug()<<"getFreeBuff: threadBuff.length():"+QString::number(threadBuff.length());
    if(threadBuff.length()<THREAD_NUM)
    {
        return threadBuff.length();
    }

    return -1;
}

void ThreadPool::freeBuff(int tid)
{
    buffMutex.lock();
    for(int i=0;i<threadBuff.length();++i)
    {
        if(threadBuff.at(i)->getTid()==tid)
        {
            exitThread(i);
            threadBuff.removeAt(i);
            qThreadList.removeAt(i);
        }
    }
    buffMutex.unlock();
}

/*
 * 检查线程缓冲区中是否有重复连接，如果是重复连接返回位置，否则返回-1
*/
int ThreadPool::checkConnection(unsigned long ipAddr)
{
    buffMutex.lock();
    for(int i=0;i<threadBuff.length();i++)
    {
        /* 查找重复连接 */
        if(threadBuff.at(i)->getIpAddr()==ipAddr)
        {
            buffMutex.unlock();
            return i;
        }
    }
    buffMutex.unlock();
    return -1;//不存在该连接
}

ThreadOperation *ThreadPool::getIndexThread(int index) const
{
    return threadBuff.at(index);
}

void ThreadPool::exitThread(int index)
{
    //退出线程
    qThreadList.at(index)->quit();
    //回收资源
    qThreadList.at(index)->wait();
    buffMutex.lock();
    delete qThreadList.at(index);
    buffMutex.unlock();
}

void ThreadPool::exitThread(QThread *qt)
{
    qt->quit();
    qt->wait();
}

bool ThreadPool::addThread(ThreadOperation *bt,QThread* qt)
{
    if(threadBuff.length()<THREAD_NUM)
    {
        buffMutex.lock();
        threadBuff.append(bt);
        qThreadList.append(qt);
        buffMutex.unlock();
        return true;
    }
    return false;
}

ThreadOperation *ThreadPool::searchThread(unsigned int ipAddr, int port)
{
    buffMutex.lock();
    foreach(ThreadOperation* bt,threadBuff)
    {
        if(bt->getIpAddr()==ipAddr && bt->getConnFd()==port)
        {
            buffMutex.unlock();
            return bt;
        }
    }
    buffMutex.unlock();
    return nullptr;
}

ThreadOperation *ThreadPool::searchThread(int pos)
{
    if(pos<0 && pos>=threadBuff.length())return nullptr;
    else return threadBuff.at(pos);
}

QThread *ThreadPool::searchQThread(int pos)
{
    if(pos<0 && pos>=qThreadList.length())return nullptr;
    else return qThreadList.at(pos);

}

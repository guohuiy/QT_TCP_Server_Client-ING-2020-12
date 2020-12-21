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
    buffMutex.lock();
    if(threadBuff.length()<THREAD_NUM)
    {
        return threadBuff.length();
    }

    return -1;
}

void ThreadPool::freeBuff(int index)
{
    buffMutex.lock();
    if(index<threadBuff.length() && threadBuff.at(index)->getBuffStatus()==threadBuff.at(index)->THREAD_OCCUPIED)
    {
        exitThread(index);
        buffMutex.lock();
        threadBuff.removeAt(index);
        qThreadList.removeAt(index);
        buffMutex.unlock();
    }
    buffMutex.unlock();
}

/*
 * 检查线程缓冲区中是否有重复连接，如果是重复连接返回位置，否则返回-1
*/
int ThreadPool::checkConnection(unsigned long ipAddr)
{
    for(int i=0;i<THREAD_NUM;i++)
    {
        /* 查找重复连接 */
        if(threadBuff.at(i)->getIpAddr()==ipAddr)
        {
            return i;
        }
    }

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
    foreach(ThreadOperation* bt,threadBuff)
    {
        if(bt->getIpAddr()==ipAddr && bt->getConnFd()==port)
            return bt;
    }
    return nullptr;
}

ThreadOperation *ThreadPool::searchThread(int pos)
{
    if(pos<0 || pos>=threadBuff.length()) return nullptr;
    return threadBuff.at(pos);
}

void ThreadPool::setThreadPoolMutexLock()
{
    buffMutex.lock();
}

void ThreadPool::setThreadPoolMutexUnlock()
{
    buffMutex.unlock();
}


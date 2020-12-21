#include "basethread.h"
#include <QDataStream>

BaseThread::BaseThread(QObject *parent) : QObject(parent)
{
    buffIndex=-1;     // 线程缓冲区的索引号
    tid=0;            // 保存对应线程的线程号
    ipAddr=0;  // 保存对应的客户机的IP地址
    connFd=0;        // 该线程使用的连接套接字描述符
    buffStatus=THREAD_FREED;    // 线程缓冲区的状态
}

BaseThread::BaseThread(int buffIndex, int tid, unsigned long ipAddr, int connFd, int buffStatus)
{
    this->buffIndex=buffIndex;
    this->tid=tid;
    this->ipAddr=ipAddr;
    this->connFd=connFd;
    this->buffStatus=buffStatus;
}

int BaseThread::getBuffIndex() const
{
    return buffIndex;
}

void BaseThread::setBuffIndex(int value)
{
    buffIndex = value;
}

int BaseThread::getTid() const
{
    return tid;
}

void BaseThread::setTid(int value)
{
    tid = value;
}

unsigned long BaseThread::getIpAddr() const
{
    return ipAddr;
}

void BaseThread::setIpAddr(unsigned long value)
{
    ipAddr = value;
}

int BaseThread::getConnFd() const
{
    return connFd;
}

void BaseThread::setConnFd(int value)
{
    connFd = value;
}

int BaseThread::getBuffStatus() const
{
    return buffStatus;
}

void BaseThread::setBuffStatus(int value)
{
    buffStatus = value;
}


#ifndef BASETHREAD_H
#define BASETHREAD_H

#include <QObject>
#include "message.h"

class BaseThread : public QObject
{
    Q_OBJECT
public:
    enum{THREAD_FREED,THREAD_OCCUPIED};//线程状态

    BaseThread(QObject *parent = nullptr);
    BaseThread(int buffIndex,int tid,unsigned long ipAddr,int connFd,int buffStatus);

    int getBuffIndex() const;
    void setBuffIndex(int value);

    int getTid() const;
    void setTid(int value);

    unsigned long getIpAddr() const;
    void setIpAddr(unsigned long value);

    int getConnFd() const;
    void setConnFd(int value);

    int getBuffStatus() const;
    void setBuffStatus(int value);   

private:
    int buffIndex;     // 线程缓冲区的索引号
    int tid;            // 保存对应线程的线程号
    unsigned long ipAddr;  // 保存对应的客户机的IP地址
    int	connFd;        // 该线程使用的连接套接字描述符
    int	buffStatus;    // 线程缓冲区的状态
signals:

};

#endif // BASETHREAD_H

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include "threadoperation.h"
#include "infoprocess.h"
#include <QThread>
#include <QMutex>

class ThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPool(QObject *parent = nullptr);
    ~ThreadPool();

    //void initThreadBuff();
    int getFreeBuff();
    void freeBuff(int tid);
    int checkConnection(unsigned long ipAddr,unsigned int port);

    ThreadOperation* getIndexThread(int index)const;
    void exitThread(int index);
    void exitThread(QThread* qt);
    bool addThread(ThreadOperation* bt,QThread* qt);
    ThreadOperation* searchThread(unsigned int ipAddr,int port);
    ThreadOperation* searchThread(int pos);
    QThread *searchQThread(int pos);
private:
    /* 服务器端的线程缓冲区的最大数量 */
    const int THREAD_NUM=128;

    QList<QThread*> qThreadList;
    QList<ThreadOperation*> threadBuff;
    InfoProcess *info;
    /*
     * 用于线程缓冲区互斥使用的互斥锁
     * 由于当主线程分配线程缓冲区时需要检测buff_status变量的值
     * 而服务线程在退出前，需要将它使用的线程缓冲区释放
     * 所谓释放就是需要修改buff_status变量的值
     * 所以主线程和服务线程间需要对buff_status进行互斥
     * 可以为每一个buff_status变量设置一个互斥锁，但这样需要较多的系统资源
     * 这里只使用了一个互斥锁来对结构数组中的所有buff_status变量进行互斥保护。*/
    QMutex buffMutex;

signals:

};

#endif // THREADPOOL_H

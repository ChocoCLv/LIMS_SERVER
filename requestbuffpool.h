#ifndef REQUESTBUFFPOOL_H
#define REQUESTBUFFPOOL_H

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QDebug>
#include <QSemaphore>
#include <QHostAddress>

#include "clientrequest.h"
#include "commmodule.h"
#include "logmodule.h"


/***
 * 收取来自CommModule的信息，并记录在ClientRequest中
 * 维护一个ClientRequest队列
 * 上层的RequestParseModule从此取出请求并解析
 *
 * 存在的问题：
 * 目前工作方式为上层RequestParseModule模块为一个独立线程
 * 但是由于缓冲池在上层模块中创建，所以这两个部分仍然不是独立运行
 * 需要将本模块也独立为一个线程
 * **/

class RequestBuffPool : public QThread
{
    Q_OBJECT
public:
    explicit RequestBuffPool(QObject *parent = 0);
    ClientRequest * getClientRequest();
    ~RequestBuffPool();

private:
    QQueue<ClientRequest*> clientRequestQueue;
    CommModule *commModule;
    LogModule *logModule = LogModule::getInstance();
    QSemaphore requestNum;

protected:
    void run();

signals:

public slots:
    void newRequest(QHostAddress cAddr,QByteArray req);
};

#endif // REQUESTBUFFPOOL_H

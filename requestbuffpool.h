#ifndef REQUESTBUFFPOOL_H
#define REQUESTBUFFPOOL_H

#include <QObject>
#include <QQueue>

#include "clientrequest.h"
#include "commmodule.h"


/***
 * 收取来自CommModule的信息，并记录在ClientRequest中
 * 维护一个ClientRequest队列
 * 上层的RequestParseModule从此取出请求并解析
 * **/


/***
 *
 *
 * **/

class RequestBuffPool : public QObject
{
    Q_OBJECT
public:
    explicit RequestBuffPool(QObject *parent = 0);
    bool hasClientRequest();
    ClientRequest * getClientRequest();
    ~RequestBuffPool();

private:
    QQueue<ClientRequest*> clientRequestQueue;
    CommModule *commModule = CommModule::getInstance();

signals:

public slots:
    void newRequest(QString cIp,QByteArray req);
};

#endif // REQUESTBUFFPOOL_H

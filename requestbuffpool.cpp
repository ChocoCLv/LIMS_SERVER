#include "requestbuffpool.h"

RequestBuffPool::RequestBuffPool(QObject *parent) : QObject(parent)
{
    connect(commModule,SIGNAL(getNewRequest(QString,QByteArray)),this,SLOT(newRequest(QString,QByteArray)));
}

void RequestBuffPool::newRequest(QString cIp, QByteArray req)
{
    ClientRequest *cr = new ClientRequest();
    cr->setRequest(cIp,req);
    clientRequestQueue.enqueue(cr);
}

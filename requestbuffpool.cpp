#include "requestbuffpool.h"

RequestBuffPool::RequestBuffPool(QObject *parent) : QObject(parent)
{
    connect(commModule,SIGNAL(getNewRequest(QString,QByteArray)),this,SLOT(newRequest(QString,QByteArray)));
}

void RequestBuffPool::newRequest(QString cIp, QByteArray req)
{
    ClientRequest *cr = new ClientRequest();
    if(cr->setRequest(cIp,req)){
        clientRequestQueue.enqueue(cr);
    }else{
        delete cr;
    }

}

bool RequestBuffPool::hasClientRequest()
{
    if(clientRequestQueue.size()>0){
        return true;
    }
    return false;
}

ClientRequest* RequestBuffPool::getClientRequest()
{
    return clientRequestQueue.dequeue();
}

RequestBuffPool::~RequestBuffPool()
{
    while(clientRequestQueue.size()!=0){
        ClientRequest *cr = clientRequestQueue.dequeue();
        delete cr;
    }
}

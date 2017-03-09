#include "requestbuffpool.h"

RequestBuffPool::RequestBuffPool(QObject *parent) : QThread(parent)
{

}

void RequestBuffPool::newRequest(QString cIp, QByteArray req)
{
    ClientRequest *cr = new ClientRequest();
    if(cr->setRequest(cIp,req)){
        emit logModule->log("request buff pool:request enqueue");
        clientRequestQueue.enqueue(cr);
        requestNum.release(1);
    }else{
        delete cr;
    }
}


ClientRequest* RequestBuffPool::getClientRequest()
{
    requestNum.acquire(1);
    return clientRequestQueue.dequeue();
}

void RequestBuffPool::run()
{
    commModule = new CommModule();
    connect(commModule,SIGNAL(getNewRequest(QString,QByteArray)),
           this,SLOT(newRequest(QString,QByteArray)),Qt::DirectConnection);

    this->exec();
}

RequestBuffPool::~RequestBuffPool()
{
    while(clientRequestQueue.size()!=0){
        ClientRequest *cr = clientRequestQueue.dequeue();
        delete cr;
    }
}

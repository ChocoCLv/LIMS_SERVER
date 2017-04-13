#include "requestbuffpool.h"

RequestBuffPool::RequestBuffPool(QObject *parent) : QThread(parent)
{

}

void RequestBuffPool::newRequest(QHostAddress cAddr, QByteArray req)
{
    ClientRequest *cr = new ClientRequest();
    if(cr->setRequest(cAddr,req)){
        emit logModule->log("request buff pool:request enqueue ");
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
    commModule = CommModule::getInstance();//第一次获取CommModule的实例，确保通信模块在子线程中运行

    connect(commModule,SIGNAL(getNewRequest(QHostAddress,QByteArray)),
           this,SLOT(newRequest(QHostAddress,QByteArray)),Qt::DirectConnection);

    this->exec();
}

RequestBuffPool::~RequestBuffPool()
{
    while(clientRequestQueue.size()!=0){
        ClientRequest *cr = clientRequestQueue.dequeue();
        delete cr;
    }
}

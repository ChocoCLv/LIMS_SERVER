#include "requestbuffpool.h"

RequestBuffPool::RequestBuffPool(QObject *parent) : QThread(parent)
{
    moveToThread(this);//确保后续操作均在子线程中进行

    connect(commModule,SIGNAL(getNewRequest(QString,QByteArray)),
            this,SLOT(newRequest(QString,QByteArray)));

   qDebug()<<"RequestBuffPool thread id:"<<QThread::currentThreadId();
   qDebug()<<"request num:"<<requestNum.available();

   QByteArray data;
   newRequest("",data);
}

void RequestBuffPool::newRequest(QString cIp, QByteArray req)
{
    qDebug()<<"RequestBuffPool slot func thread id:"<<QThread::currentThreadId();
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

}

RequestBuffPool::~RequestBuffPool()
{
    while(clientRequestQueue.size()!=0){
        ClientRequest *cr = clientRequestQueue.dequeue();
        delete cr;
    }
}

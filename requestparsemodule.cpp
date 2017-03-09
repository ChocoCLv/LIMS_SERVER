#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QThread(parent)
{
    //moveToThread(this);
    requestBuffPool = new RequestBuffPool();

    qDebug()<<"RequestParseModule thread id:"<<QThread::currentThreadId();
}

void RequestParseModule::run()
{
    //requestBuffPool = new RequestBuffPool();
    emit logModule->log("thread run");
    qDebug()<<"RequestParseModule run thread id:"<<QThread::currentThreadId();
    forever{
        ClientRequest *cr = requestBuffPool->getClientRequest();
        emit logModule->log("requeest parse module:parse request");
        parseRequest(cr->getReqContent());
    }
}


void RequestParseModule::parseRequest(QJsonObject req)
{
    int rt = req.find("RequestType").value().toInt();
    switch(rt)
    {
    case LOGIN:
    {
        break;
    }
     default:
        break;
    }

}



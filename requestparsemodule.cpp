#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QThread(parent)
{
    requestBuffPool = new RequestBuffPool();
}

void RequestParseModule::run()
{
    while(requestBuffPool->hasClientRequest())
    {
        ClientRequest *cr = requestBuffPool->getClientRequest();
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



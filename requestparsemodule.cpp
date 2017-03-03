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
    RequestType rt = req.find("RequestType");
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



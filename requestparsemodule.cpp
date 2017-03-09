#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QThread(parent)
{
    requestBuffPool = new RequestBuffPool();
    requestBuffPool->start();
}

void RequestParseModule::run()
{

    databaseModule = new DataBaseModule();

    forever{
        ClientRequest *cr = requestBuffPool->getClientRequest();
        emit logModule->log("request parse module:parse request");
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



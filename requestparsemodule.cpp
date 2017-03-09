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
    QString username = req.find("username").value().toString();
    QString password = req.find("password").value().toString();
    qDebug()<<"username:"<<username;
    qDebug()<<"password:"<<password;
}



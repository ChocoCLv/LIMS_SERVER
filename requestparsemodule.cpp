#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QThread(parent)
{
    requestBuffPool = new RequestBuffPool();
    requestBuffPool->start();
}

void RequestParseModule::run()
{

    databaseModule = new DataBaseModule();
    ClientRequest *cr;

    forever{
        qDebug()<<"request parse module run thread id:"<<QThread::currentThreadId();
        cr = requestBuffPool->getClientRequest();
        emit logModule->log("request parse module:parse request");
        parseRequest(cr);
    }
}


void RequestParseModule::parseRequest(ClientRequest *cr)
{
    //QJsonObject req = cr->getReqContent();
    //int rt = req.find("requesttype").value().toInt();
    int rt = 0;
    switch(rt)
    {
    case LOGIN:
        processLoginRequest(cr);
        break;
    default:
        break;
    }

}

void RequestParseModule::processLoginRequest(ClientRequest *cr)
{
    QString username = cr->getReqContent().find("USERNAME").value().toString();
    QString password = cr->getReqContent().find("PASSWORD").value().toString();
    QString result;
    QString user_type;
    databaseModule->queryLoginInformation(username,result,user_type);
    emit logModule->log("correct password:"+result+" user type:"+user_type);
    if(result == password){
        QJsonObject jo;
        jo.insert("LOGIN_STATUS",QString("SUCCESS"));
        jo.insert("USERTYPE",user_type);
        cr->sendResponse(jo);
    }
}



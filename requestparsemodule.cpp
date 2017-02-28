#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QObject(parent)
{
    connect(commModule,SIGNAL(getNewRequest(QByteArray)),this,SLOT(parseRequest(QByteArray)));
}


void RequestParseModule::parseRequest(QByteArray req)
{
    emit logModule->log("process datagram");

    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    QJsonObject jo = jd.object();
    emit logModule->log(jo);

    int rt = jo.find("RequestType").value().toInt();
    switch(rt)
    {
    case LOGIN:
    {
        QString username = jo.find("Username").value().toString();
        QString password = jo.find("Password").value().toString();

        break;
    }

    default:
        break;
    }
}



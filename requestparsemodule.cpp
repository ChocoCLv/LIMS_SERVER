#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QObject(parent)
{

}


void RequestParseModule::parseRequest(QByteArray req)
{

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



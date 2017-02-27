#include "requestparsemodule.h"

RequestParseModule::RequestParseModule(QObject *parent) : QObject(parent)
{
    connect(commModule,SIGNAL(getNewRequest(QByteArray)),this,SLOT(parseRequest(QByteArray)));
}


void RequestParseModule::parseRequest(QByteArray req)
{

    qDebug()<<"process datagram"<<endl;
    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    QJsonObject jo = jd.object();
    qDebug()<<jo<<endl;

    switch(jo.find("RequestType").value().toInt())
    {
    case LOGIN:
    {
        //QString username = jo.find("Username").value().toString();
        //QString password = jo.find("Password").value().toString();
        QString username = jo.find("Username").value().toString();
        QString password = jo.find("Password").value().toString();
        tryToLogin(username,password);
        break;
    }

    default:
        break;
    }
}

bool RequestParseModule::tryToLogin(QString un, QString pwd)
{
    QString correct_pwd = databaseModule->query(un,"password");
    if(pwd == correct_pwd){
        return true;
    }
    return false;
}

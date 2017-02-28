#include "clientrequest.h"

ClientRequest::ClientRequest(QObject *parent) : QObject(parent)
{

}

void ClientRequest::setRequest(QString cIp,QByteArray req)
{
    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    QJsonObject jo = jd.object();

    rt = jo.find("RequestType").value().toInt();

    requestContent_js = jo;
    clientIp = cIp;
}

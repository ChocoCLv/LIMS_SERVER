#include "clientrequest.h"

ClientRequest::ClientRequest(QObject *parent) : QObject(parent)
{

}

bool ClientRequest::setRequest(QString cIp,QByteArray req)
{
    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    if(jpe.error == QJsonParseError::NoError)
    {
        QJsonObject jo = jd.object();
        requestContent_js = jo;
        clientIp = cIp;
        return true;
    }
    emit logModule->log(jpe.errorString());
    return false;

}

QJsonObject ClientRequest::getReqContent()
{
    return requestContent_js;
}

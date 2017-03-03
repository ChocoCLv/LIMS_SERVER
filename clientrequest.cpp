#include "clientrequest.h"

ClientRequest::ClientRequest(QObject *parent) : QObject(parent)
{

}

bool ClientRequest::setRequest(QString cIp,QByteArray req)
{
    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    if(jpe == QJsonParseError::NoError)
    {
        QJsonObject jo = jd.object();
        rt = jo.find("RequestType").value().toInt();
        requestContent_js = jo;
        clientIp = cIp;
        return true;
    }
    emit log->log(jpe.errorString());
    return false;

}

QJsonObject ClientRequest::getReqContent()
{
    return requestContent_js;
}

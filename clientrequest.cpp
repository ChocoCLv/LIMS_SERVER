#include "clientrequest.h"

ClientRequest::ClientRequest(QObject *parent) : QObject(parent)
{

}

bool ClientRequest::setRequest(QHostAddress cAddr,QByteArray req)
{
    QJsonParseError jpe;
    QJsonDocument jd = QJsonDocument::fromJson(req,&jpe);

    if(jpe.error == QJsonParseError::NoError)
    {
        QJsonObject jo = jd.object();
        requestContent_js = jo;
        clientAddr = cAddr;
        return true;
    }
    emit logModule->log(jpe.errorString());
    return false;

}

void ClientRequest::sendResponse(QJsonObject resp)
{
    commModule->sendData(clientAddr,resp);
}

QJsonObject ClientRequest::getReqContent()
{
    return requestContent_js;
}

ClientRequest::~ClientRequest()
{

}

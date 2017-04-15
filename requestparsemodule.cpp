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
        cr = requestBuffPool->getClientRequest();
        emit logModule->log("request parse module:parse request");
        parseRequest(cr);
    }
}


void RequestParseModule::parseRequest(ClientRequest *cr)
{
    QJsonObject req = cr->getReqContent();
    QString rt = req.find("REQUEST_TYPE").value().toString();
    if(rt == "LOGIN"){
        processLoginRequest(cr);
    }else if(rt == "ADD_DEVICE"){
        processAddDeviceRequest(cr);
    }
}

void RequestParseModule::processLoginRequest(ClientRequest *cr)
{
    QString userId = cr->getReqContent().find("USER_ID").value().toString();
    QString password = cr->getReqContent().find("PASSWORD").value().toString();
    QString result;
    QString user_type;
    QString username;
    databaseModule->queryLoginInformation(userId,result,user_type);
    emit logModule->log(userId+"correct password:"+result+" user type:"+user_type);
    if(result == password){
        username = databaseModule->queryUserNamaByUserId(userId);
        QJsonObject jo;
        jo.insert("LOGIN_STATUS",QString("SUCCESS"));
        jo.insert("USER_NAME",username);
        jo.insert("USERTYPE",user_type);
        cr->sendResponse(jo);
    }else{
        QJsonObject jo;
        jo.insert("LOGIN_STATUS",QString("FAILED"));
        cr->sendResponse(jo);
    }
}

void RequestParseModule::processAddDeviceRequest(ClientRequest *cr)
{
    QString devicePrincipal = cr->getReqContent().find("DEVICE_PRINCIPAL").value().toString();
    QString deviceName = cr->getReqContent().find("DEVICE_NAME").value().toString();
    QString deviceType = cr->getReqContent().find("DEVICE_TYPE").value().toString();
    QString deviceId = databaseModule->addDevice(deviceName,deviceType,devicePrincipal);
    if(deviceId!=-1){
        QJsonObject jo;
        jo.insert("ADD_STATUS","SUCCESS");
        jo.insert("DEVICE_ID",deviceId);
        cr->sendResponse(jo);
    }
}

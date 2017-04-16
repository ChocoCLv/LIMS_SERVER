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
    QString devicePrincipalId = cr->getReqContent().find("DEVICE_PRINCIPAL_ID").value().toString();
    QString deviceName = cr->getReqContent().find("DEVICE_NAME").value().toString();
    QString deviceType = cr->getReqContent().find("DEVICE_TYPE").value().toString();
    QJsonObject::iterator deviceIdIterator = cr->getReqContent().find("DEVICE_ID");
    QString deviceId;
    QJsonObject resp;
    if(deviceIdIterator==cr->getReqContent().end()){
        deviceId = QString::number(databaseModule->getMaxDeviceId()+1);
        resp.insert("DEVICE_ID",deviceId);
    }else{
        deviceId = deviceIdIterator.value().toString();
    }

    bool addStatus = databaseModule->addDevice(deviceId,deviceName,deviceType,devicePrincipalId);

    if(addStatus){
        resp.insert("ADD_STATUS","SUCCESS");
    }else{
        resp.insert("ADD_STATUS","FAILED");
    }
    cr->sendResponse(resp);
}

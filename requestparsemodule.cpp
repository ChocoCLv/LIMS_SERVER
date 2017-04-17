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
    }else if(rt == "UPDATE_DEVICE_STATUS"){
        processUpdateDevcieStatusRequest(cr);
    }else if(rt == "BORROW_DEVICE"){
        processBorrowDeviceRequest(cr);
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

void RequestParseModule::processUpdateDevcieStatusRequest(ClientRequest *cr)
{
    QJsonObject req = cr->getReqContent();
    QString deviceId = req.find("DEVICE_ID").value().toString();
    QString deviceStatus = req.find("DEVICE_CURRENT_STATUS").value().toString();
    QString deviceLoc = req.find("DEVICE_CURRENT_LOCATION").value().toString();
    QString deviceComments = req.find("DEVICE_COMMENTS").value().toString();
    bool updateStatus = databaseModule->
            updateDeviceStatus(deviceId,deviceLoc,deviceStatus,deviceComments);
    QJsonObject resp;
    if(updateStatus){
        resp.insert("UPDATE_STATUS","SUCCESS");
    }else{
        resp.insert("UPDATE_STATUS","FAILED");
    }
    cr->sendResponse(resp);
}

void RequestParseModule::processBorrowDeviceRequest(ClientRequest *cr)
{
    QJsonObject req = cr->getReqContent();
    QString deviceId = req.find("DEVICE_ID").value().toString();
    QString studentId = req.find("STUDENT_ID").value().toString();

    bool borrowStatus = databaseModule->
            borrowDevice(deviceId,studentId);
    QJsonObject resp;
    if(borrowStatus){
        resp.insert("BORROW_STATUS","SUCCESS");
    }else{
        resp.insert("BORROW_STATUS","FAILED");
    }
    cr->sendResponse(resp);
}

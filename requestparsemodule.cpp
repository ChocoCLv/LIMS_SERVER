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
    }else if(rt == "PUBLISH_PROJECT"){
        processPublishExperimentRequest(cr);
    }else if(rt == "GET_COURSE_LIST"){
        processGetCourseListRequest(cr);
    }else if(rt == "GET_PROJECT_INFO"){
        processGetProjectInfoRequest(cr);
    }else if(rt == "SIGN_IN"){
        processSignInRequest(cr);
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
        jo.insert("USER_TYPE",user_type);
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
    QString deviceLocDefault = cr->getReqContent().find("DEVICE_LOC_DEFAULT").value().toString();
    QString deviceId = cr->getReqContent().find("DEVICE_ID").value().toString();
    QJsonObject resp;

    bool addStatus = databaseModule->addDevice(deviceId,deviceName,deviceType,devicePrincipalId,deviceLocDefault);

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

    QString newestAction = databaseModule->getDeviceStatus(deviceId);
    QJsonObject resp;

    if(newestAction == "BORROW"){
        resp.insert("BORROW_STATUS","FAILED");
        resp.insert("DESCRIPTION","当前设备处于借出状态，请提醒管理员收回！");
        cr->sendResponse(resp);
        return;
    }

    bool borrowStatus = databaseModule->
            borrowDevice(deviceId,studentId);

    if(borrowStatus){
        resp.insert("BORROW_STATUS","SUCCESS");
    }else{
        resp.insert("BORROW_STATUS","FAILED");
    }
    cr->sendResponse(resp);

    QString deviceType = req.find("DEVICE_TYPE").value().toString();
    if(deviceType == "电脑"){
        QString deviceIp = req.find("DEVICE_IP").value().toString();
        distributeFileToDevice(deviceIp);
    }
}

void RequestParseModule::distributeFileToDevice(QString deviceIp)
{

}

void RequestParseModule::processPublishExperimentRequest(ClientRequest *cr)
{
    QJsonObject req = cr->getReqContent();
    QString courseName = req.find("COURSE_NAME").value().toString();
    QString projectName = req.find("PROJECT_NAME").value().toString();
    QString projectLoc = req.find("PROJECT_LOC").value().toString();
    QString projectTeacherId = req.find("TEACHER_ID").value().toString();
    QString projectDate = req.find("PROJECT_DATE").value().toString();
    QString projectStartTime = req.find("PROJECT_START_TIME").value().toString();
    QString projectEndTime = req.find("PROJECT_END_TIME").value().toString();

    QJsonObject resp;
    Util util;
    if(!util.isTimeConflict(projectStartTime,projectEndTime,databaseModule->getLabUseTime(projectLoc,projectDate))){
        bool publishResult = databaseModule->publishExperiment(projectTeacherId,courseName,projectName,projectLoc,projectDate,projectStartTime,projectEndTime);
        if(publishResult){
            resp.insert("PUBLISH_RESULT","SUCCESS");
        }else{
            resp.insert("PUBLISH_RESULT","FAILED");
        }
    }else{
        resp.insert("PUBLISH_RESULT","FAILED");
        resp.insert("PUBLISH_DESCRIPTION","时间段冲突");
    }

    cr->sendResponse(resp);
}

void RequestParseModule::processGetCourseListRequest(ClientRequest *cr)
{
    QString teacherId = cr->getReqContent().find("TEACHER_ID").value().toString();
    QJsonArray courseArray = databaseModule->getCourseListByTeacherId(teacherId);
    QJsonObject resp;
    if(courseArray.isEmpty()){
        resp.insert("GET_RESULT","FAILED");
    }else{
        resp.insert("GET_RESULT","SUCCESS");
        resp.insert("COURSE_ARRAY",courseArray);
    }
    cr->sendResponse(resp);
}

void RequestParseModule::processGetProjectInfoRequest(ClientRequest *cr)
{
    QString studentId = cr->getReqContent().find("STUDENT_ID").value().toString();
    QJsonArray projectsInfo = databaseModule->getProjectInfoByStudentId(studentId);
    QJsonObject resp;
    if(projectsInfo.isEmpty()){
        resp.insert("GET_RESULT","FAILED");
    }else{
        resp.insert("GET_RESULT","SUCCESS");
        resp.insert("PROJECTS_INFO",projectsInfo);
    }
    cr->sendResponse(resp);
}

void RequestParseModule::processSignInRequest(ClientRequest *cr)
{
    QString teacherId = cr->getReqContent().find("TEACHER_ID").value().toString();
    QString studentId = cr->getReqContent().find("STUDENT_ID").value().toString();
    QString courseName = cr->getReqContent().find("COURSE_NAME").value().toString();
    QString projectName = cr->getReqContent().find("PROJECT_NAME").value().toString();

    QPair<QString,QString> netInfo = databaseModule->getLabNetInfoByProjectName(projectName);

    Util util;
    QJsonObject resp;
    if(util.isInTheSameSubnet(netInfo,cr->getClientAddr())){
        bool signInResult = databaseModule->signIn(studentId,teacherId,courseName,projectName);
        if(signInResult){
            resp.insert("SIGNIN_RESULT","SUCCESS");
        }else{
            resp.insert("SIGNIN_RESULT","FAILED");
        }
    }else{
        resp.insert("SIGNIN_RESULT","FAILED");
        resp.insert("SIGNIN_DESCRIPTION","检查是否连接实验室WIFI");
    }
    cr->sendResponse(resp);
}

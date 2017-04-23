#include "databasemodule.h"

DataBaseModule::~DataBaseModule()
{

}

DataBaseModule::DataBaseModule(QObject *parent) : QObject(parent)
{
    initDb();
}


void DataBaseModule::initDb()
{
    if(!connectToDb()){
        return;
    }
}

void DataBaseModule::queryLoginInformation(QString user_id,QString &result,QString &user_type)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("SELECT user_password,user_type FROM basic_user_information WHERE user_id ='%1'")
            .arg(user_id);
    query.exec(q_str);
    query.next();

    result = query.value(0).toString();
    user_type = query.value(1).toString();
}

bool DataBaseModule::connectToDb()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(DB_NAME);
    db.setHostName(DB_SERVER_ADDR);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);
    db.setPort(DB_SERVER_PORT);

    if(!db.open()){
        emit logModule->log("can't open database");
        return false;
    }
    emit logModule->log("database open successfully");
    return true;
}

QString DataBaseModule::queryUserNamaByUserId(QString user_id)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("SELECT user_name FROM basic_user_information WHERE user_id ='%1'")
            .arg(user_id);
    query.exec(q_str);
    query.next();

    return query.value(0).toString();
}

bool DataBaseModule::addDevice(QString deviceId, QString name, QString type, QString principal, QString locDefault)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("INSERT INTO device_information(device_id,device_name,device_principal_id,device_type,device_belong_to) VALUES ('%1', '%2', '%3','%4','%5')")
            .arg(deviceId).arg(name).arg(principal).arg(type).arg(locDefault).toUtf8();

    query.exec(q_str);
    if(!query.isActive()){
        qDebug()<<query.lastError();
        qDebug()<<q_str;
        return false;
    }
    return true;
}

bool DataBaseModule::updateDeviceStatus(
        QString deviceId, QString deviceLoc, QString deviceStatus, QString deviceComments)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("INSERT INTO device_status_log(device_id,device_loc,device_status,device_comments) VALUES ('%1', '%2', '%3','%4')")
            .arg(deviceId).arg(deviceLoc).arg(deviceStatus).arg(deviceComments).toUtf8();
    query.exec(q_str);
    if(!query.isActive()){
        qDebug()<<query.lastError();
        qDebug()<<q_str;
        return false;
    }
    return true;
}

bool DataBaseModule::borrowDevice(QString deviceId, QString studentId)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("INSERT INTO device_borrow_log(device_id,student_id) VALUES ('%1', '%2')")
            .arg(deviceId).arg(studentId).toUtf8();
    query.exec(q_str);
    if(!query.isActive()){
        qDebug()<<query.lastError();
        qDebug()<<q_str;
        return false;
    }
    return true;
}

bool DataBaseModule::publishExperiment(QString teacherId, QString courseName,QString projectName, QString loc, QString date, QString stime, QString etime)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("INSERT INTO project_publish_records(course_name,project_name,teacher_id,loc,project_date,start_time,end_time) VALUES ('%1', '%2','%3','%4','%5','%6','%7')")
            .arg(courseName).arg(projectName).arg(teacherId).arg(loc).arg(date).arg(stime).arg(etime).toUtf8();

    query.exec(q_str);
    if(!query.isActive()){
        qDebug()<<query.lastError();
        qDebug()<<q_str;
        return false;
    }
    return true;
}

QList<QPair<QString,QString> > DataBaseModule::getLabUseTime(QString lab,QString date)
{
    QList<QPair<QString,QString> > useTime;
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("SELECT start_time,end_time FROM project_publish_records WHERE project_date ='%1' and loc ='%2'")
            .arg(date).arg(lab).toUtf8();

    query.exec(q_str);

    if(!query.isActive()){
        qDebug()<<query.lastError();

        return useTime;
    }
    while(query.next()){
        QString stime = query.value(0).toString();
        QString etime = query.value(1).toString();
        useTime.append(QPair<QString,QString>(stime,etime));
    }

    return useTime;
}

QString DataBaseModule::getCourseListByTeacherId(QString teacherId)
{
    QString courseListString;
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("SELECT course_name FROM class_participants WHERE teacher_id ='%1'")
            .arg(teacherId).toUtf8();

    query.exec(q_str);

    if(!query.isActive()){
        qDebug()<<query.lastError();

        return courseListString;
    }
    if(query.next())
        courseListString.append(query.value(0).toString());
    while(query.next()){
        QString cn = query.value(0).toString();
        courseListString.append(","+cn);
    }

    return courseListString;
}

QString DataBaseModule::getProjectInfoByStudentId(QString studentId)
{
    QString projectsInfo;
    QList<QPair<QString,QString> > classes_info;//teacher_id + course_name

    QString q_str;
    QSqlQuery query(db);
    q_str = QString("SELECT teacher_id,course_name FROM class_participants WHERE student_id ='%1'")
            .arg(studentId).toUtf8();

    query.exec(q_str);

    if(!query.isActive()){
        qDebug()<<query.lastError();
        return projectsInfo;
    }

    while(query.next()){
        QString tid = query.value(0).toString();
        QString cname = query.value(1).toString();
        classes_info.append(QPair<QString,QString>(tid,cname));
    }
    QPair<QString,QString> class_info;
    foreach (class_info, classes_info) {
        QString courseName = class_info.second;
        QString teacherId = class_info.first;
        q_str = QString("SELECT * FROM project_publish_records WHERE teacher_id = '%1' and course_name ='%2' ")
                .arg(teacherId).arg(courseName).toUtf8();
        query.exec(q_str);
        while(query.next()){
            QString projectName = query.value(2).toString();
            QString projectDate =  query.value(4).toString();
            QString projectStartTime = query.value(5).toString();
            QString projectEndTime= query.value(6).toString();
            QString projectLoc= query.value(7).toString();
            projectsInfo.append(courseName+","+projectName+","+teacherId+","+projectDate+","+projectStartTime+","+projectEndTime+","+projectLoc+";");
        }
    }
    if(projectsInfo.count(";")>1){
        projectsInfo.remove(projectsInfo.size()-1,1);
    }
    return projectsInfo;
}

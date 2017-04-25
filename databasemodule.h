#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include <QJsonArray>
#include <QJsonObject>

#include "logmodule.h"
#include "global.h"

/***
 * 封装数据库操作语句
 * 不涉及数据的逻辑判断操作
 ***/

class DataBaseModule : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseModule(QObject *parent = 0);
    ~DataBaseModule();

    //查询语句根据数据库中存储相应表项的数据类型将传入参数的值转换为相应类型
    void queryLoginInformation(QString user_id,QString &result,QString &user_type);

    QString queryUserNamaByUserId(QString user_id);

    bool addDevice(QString deviceId,QString name,QString type,QString principal,QString locDefault);

    bool updateDeviceStatus(QString deviceId, QString deviceLoc, QString deviceStatus, QString deviceComments);

    bool borrowDevice(QString deviceId,QString studentId);

    bool publishExperiment(QString teacherId,QString courseName,QString projectname,QString loc,QString date,QString stime,QString etime);

    //获得实验室某一天的使用时间段
    QJsonArray getLabUseTime(QString lab,QString date);

    //根据教师ID获取该教师的所有课程
    QJsonArray getCourseListByTeacherId(QString teacherId);

    //根据学生ID获取该学生的所有项目信息
    QJsonArray getProjectInfoByStudentId(QString studentId);

    //获取设备的状态  即是否是借出状态
    QString getDeviceStatus(QString deviceId);

private:
    LogModule *logModule = LogModule::getInstance();
    QSqlDatabase db;

    void initDb();
    bool connectToDb();

signals:

public slots:
};

#endif // DATABASEMODULE_H

#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

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

    void addDevice(QString name,QString type,QString principal);

private:
    LogModule *logModule = LogModule::getInstance();
    QSqlDatabase db;

    void initDb();
    bool connectToDb();

signals:

public slots:
};

#endif // DATABASEMODULE_H

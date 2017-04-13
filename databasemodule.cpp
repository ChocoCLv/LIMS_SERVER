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

void DataBaseModule::addDevice(QString name, QString type, QString principal)
{
    QSqlQuery query(db);
    QString q_str;
    q_str = QString("INSERT INTO device_information(device_name,device_principal_id,device_type) VALUES ('%1', '%2', '%3')")
            .arg(name).arg(principal).arg(type);
    query.exec(q_str);
    if(!query.isActive()){
        qDebug()<<query.lastError();
    }
}

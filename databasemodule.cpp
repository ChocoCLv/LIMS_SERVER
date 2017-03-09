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
        qDebug()<<db.lastError()<<endl;
        return false;
    }
    emit logModule->log("database open successfully");
    return true;
}


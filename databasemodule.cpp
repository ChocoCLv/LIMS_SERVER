#include "databasemodule.h"

DataBaseModule* DataBaseModule::databaseModulle = NULL;

DataBaseModule::~DataBaseModule()
{
    delete databaseModulle;
}

DataBaseModule::DataBaseModule(QObject *parent) : QObject(parent)
{
    initDb();
}

DataBaseModule* DataBaseModule::getInstance()
{
    if(databaseModulle == NULL){
        databaseModulle = new DataBaseModule();
    }
    return databaseModulle;
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
    db.setDatabaseName("lims");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("8682502101");
    db.setPort(3306);

    if(!db.open()){
        qDebug()<<db.lastError();
        qDebug()<<"can't open database"<<endl;
        return false;
    }
    return true;
}

QString DataBaseModule::query(QString key_known, QString key_unknown)
{
    QSqlQuery q(db);
    //QString query_content = "SELECT "+key_unknown+""
    q.exec(QString("SELECT user_password FROM basic_user_information WHERE username='%1'").arg(key_known));
    q.next();
    return q.value(0).toString();
}

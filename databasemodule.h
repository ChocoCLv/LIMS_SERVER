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
 ***/

class DataBaseModule : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseModule(QObject *parent = 0);
    ~DataBaseModule();

private:
    LogModule *logModule = LogModule::getInstance();
    QSqlDatabase db;

    void initDb();
    bool connectToDb();

signals:

public slots:
};

#endif // DATABASEMODULE_H

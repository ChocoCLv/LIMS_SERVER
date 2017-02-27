#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


/***
 * 进行数据库操作
 ***/

class DataBaseModule : public QObject
{
    Q_OBJECT
public:
    static DataBaseModule * getInstance();
    ~DataBaseModule();

    QString query(QString key_known,QString key_unknown);

private:
    explicit DataBaseModule(QObject *parent = 0);
    static DataBaseModule * databaseModulle;

    QSqlDatabase db;

    void initDb();
    bool connectToDb();

signals:

public slots:
};

#endif // DATABASEMODULE_H

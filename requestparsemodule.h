#ifndef REQUESTPARSEMODULE_H
#define REQUESTPARSEMODULE_H

#include <QObject>

#include "databasemodule.h"
#include "commmodule.h"
#include "global.h"
#include "logmodule.h"

/***
 * 解析客户端的请求
 ***/


class RequestParseModule : public QObject
{
    Q_OBJECT
public:
    explicit RequestParseModule(QObject *parent = 0);

private:
    DataBaseModule *databaseModule = DataBaseModule::getInstance();
    CommModule *commModule = CommModule::getInstance();
    LogModule *logModule = LogModule::getInstance();

    bool tryToLogin(QString un,QString pwd);

signals:

public slots:

   void parseRequest(QByteArray req);
};

#endif // REQUESTPARSEMODULE_H

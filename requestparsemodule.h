#ifndef REQUESTPARSEMODULE_H
#define REQUESTPARSEMODULE_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "databasemodule.h"
#include "global.h"
#include "logmodule.h"
#include "clientrequest.h"
#include "requestbuffpool.h"

/***
 * 解析客户端的请求
 ***/


class RequestParseModule : public QThread
{
    Q_OBJECT
public:
    explicit RequestParseModule(QObject *parent = 0);

private:
    DataBaseModule *databaseModule = DataBaseModule::getInstance();
    LogModule *logModule = LogModule::getInstance();

    RequestBuffPool *requestBuffPool;

    bool tryToLogin(QString un,QString pwd);
    void parseRequest(QJsonObject req);

protected:
    void run();

signals:

public slots:


};

#endif // REQUESTPARSEMODULE_H

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
#include "util.h"

/***
 * 解析客户端的请求
 ***/


class RequestParseModule : public QThread
{
    Q_OBJECT
public:
    explicit RequestParseModule(QObject *parent = 0);

private:
    DataBaseModule *databaseModule;
    LogModule *logModule = LogModule::getInstance();

    RequestBuffPool *requestBuffPool;

    bool tryToLogin(QString un,QString pwd);
    void parseRequest(ClientRequest *cr);

    void processLoginRequest(ClientRequest *cr);
    void processAddDeviceRequest(ClientRequest *cr);
    void processBorrowDeviceRequest(ClientRequest *cr);
    void processGetCourseListRequest(ClientRequest *cr);
    void processGetProjectInfoRequest(ClientRequest *cr);
    void processPublishExperimentRequest(ClientRequest *cr);
    void processUpdateDevcieStatusRequest(ClientRequest *cr);

protected:
    void run();

signals:

public slots:


};

#endif // REQUESTPARSEMODULE_H

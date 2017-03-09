#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include <QObject>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>
#include "logmodule.h"

#include "global.h"

/***
 * 方案1：记录客户端的一个请求
 *       当本次请求尚未处理完成时拒绝该客户端接下来的请求
 *
 * 方案2：维护客户端的请求列表
 * 方案3：记录客户端的一个请求  当收到新的请求时 用新的请求覆盖之前的请求（可能增大服务器的压力）
 ***/

/***
 * 记录客户端IP地址
 * 解析出客户端的请求类型
 ***/

class ClientRequest : public QObject
{
    Q_OBJECT
public:
    explicit ClientRequest(QObject *parent = 0);
    bool setRequest(QString cIp,QByteArray req);
    QJsonObject getReqContent();

private:
    QString clientIp;
    //RequestType rt;
    QJsonObject requestContent_js;
    LogModule *logModule = LogModule::getInstance();


signals:

public slots:
};

#endif // CLIENTREQUEST_H

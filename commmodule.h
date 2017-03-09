#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QtDebug>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

#include "global.h"
#include "logmodule.h"


/***
 *
 * 与客户端通信
 *
 ***/

class CommModule : public QObject
{
    Q_OBJECT
public:
    explicit CommModule(QObject *parent = 0);
    ~CommModule();

private:
    QUdpSocket *commSocket;
    LogModule *logModule = LogModule::getInstance();
    void initSocket();

signals:
    void getNewRequest(QString clientIP,QByteArray req);

public slots:
    void readClient();

};

#endif // COMMMODULE_H

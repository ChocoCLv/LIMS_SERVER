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
#include <QThread>
#include <QJsonDocument>

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

    ~CommModule();
    static CommModule* getInstance();
    void sendData(QHostAddress cAddr,QJsonObject data);
private:
    static CommModule* commModule;
    explicit CommModule(QObject *parent = 0);
    QUdpSocket *commSocket;
    LogModule *logModule = LogModule::getInstance();
    void initSocket();


signals:
    void getNewRequest(QHostAddress clientAddr,QByteArray req);

public slots:
    void readClient();

};

#endif // COMMMODULE_H

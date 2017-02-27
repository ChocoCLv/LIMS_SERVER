#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QtDebug>
#include <QJsonArray>
#include <QJsonObject>

#include "global.h"


/***
 *
 * 与客户端通信
 *
 ***/

class CommModule : public QObject
{
    Q_OBJECT
public:
    static CommModule * getInstance();
    ~CommModule();

private:
    explicit CommModule(QObject *parent = 0);
    QUdpSocket *commSocket;
    static CommModule *commModule;
    void initSocket();

signals:
    void getNewRequest(QByteArray req);

public slots:
    void readClient();

};

#endif // COMMMODULE_H

#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QHostAddress>

class Util
{
public:
    Util();
    bool isTimeConflict(QString stime,QString etime,QJsonArray userTime);
    bool isInTheSameSubnet(QPair<QString,QString> netInfo,QHostAddress ip);
};

#endif // UTIL_H

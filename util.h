#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTime>
#include <QJsonArray>
#include <QJsonObject>

class Util
{
public:
    Util();
    bool isTimeConflict(QString stime,QString etime,QJsonArray userTime);
};

#endif // UTIL_H

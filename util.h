#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QTime>
#include <QList>
#include <QPair>


class Util
{
public:
    Util();
    bool isTimeConflict(QString stime,QString etime,QList<QPair<QString,QString> >l);
};

#endif // UTIL_H

#ifndef LOGMODULE_H
#define LOGMODULE_H

#include <QObject>

class LogModule : public QObject
{
    Q_OBJECT
public:
    explicit LogModule(QObject *parent = 0);

signals:
    //void log

public slots:
};

#endif // LOGMODULE_H

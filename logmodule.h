#ifndef LOGMODULE_H
#define LOGMODULE_H

#include <QObject>
#include <QDebug>

class LogModule : public QObject
{
    Q_OBJECT
public:
    static LogModule * getInstance();
    ~LogModule();

private:
    explicit LogModule(QObject *parent = 0);
    static LogModule * logModule;

signals:
    void log(QString l);

public slots:
};

#endif // LOGMODULE_H

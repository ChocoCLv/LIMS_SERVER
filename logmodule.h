#ifndef LOGMODULE_H
#define LOGMODULE_H

#include <QObject>

class LogModule : public QObject
{
    Q_OBJECT
public:
    explicit LogModule(QObject *parent = 0);
    static LogModule * getInstance();
    ~LogModule();

private:
    static LogModule * logModule;

signals:
    void log(QString l);

public slots:
};

#endif // LOGMODULE_H

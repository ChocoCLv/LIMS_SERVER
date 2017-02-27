#ifndef REQUESTBUFFPOOL_H
#define REQUESTBUFFPOOL_H

#include <QObject>

class RequestBuffPool : public QObject
{
    Q_OBJECT
public:
    explicit RequestBuffPool(QObject *parent = 0);

signals:

public slots:
};

#endif // REQUESTBUFFPOOL_H
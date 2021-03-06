#include "util.h"

Util::Util()
{

}

bool Util::isTimeConflict(QString stime, QString etime, QJsonArray useTime)
{
    QTime st = QTime::fromString(stime,"h:m");
    QTime et = QTime::fromString(etime,"h:m");
    QJsonArray::iterator i,j;

    for(i = useTime.begin();i!=useTime.end();i++){
        QJsonObject seTime = (*i).toObject();
        QString st_str = seTime.find("START_TIME").value().toString();
        QString et_str = seTime.find("END_TIME").value().toString();
        QTime s =QTime::fromString(st_str);
        QTime e =QTime::fromString(et_str);
        if((st<e&&st>s)||(et<e&&et>s)){
            return true;
        }else if(st<=s&&et>=e){
            return true;
        }
    }
    return false;
}

bool Util::isInTheSameSubnet(QPair<QString, QString> netInfo, QHostAddress ip)
{
    QHostAddress netAddress = QHostAddress(netInfo.first);
    QHostAddress netmask = QHostAddress(netInfo.second);

    quint32 clientNetId = ip.toIPv4Address() & netmask.toIPv4Address();
    if(netAddress.toIPv4Address() == clientNetId){
        return true;
    }else{
        return false;
    }

}

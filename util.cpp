#include "util.h"

Util::Util()
{

}

bool Util::isTimeConflict(QString stime, QString etime, QList<QPair<QString, QString> > l)
{
    QTime st = QTime::fromString(stime,"h:m");
    QTime et = QTime::fromString(etime,"h:m");
    QPair<QString,QString> p;
    foreach (p, l) {
        QTime s =QTime::fromString(p.first);
        QTime e =QTime::fromString(p.second);
        if((st<e&&st>s)||(et<e&&et>s)){
            return true;
        }else if(st<=s&&et>=e){
            return true;
        }
    }
    return false;
}

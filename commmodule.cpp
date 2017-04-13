#include "commmodule.h"

CommModule* CommModule::commModule = NULL;

CommModule::~CommModule()
{
    delete commSocket;
}

CommModule::CommModule(QObject *parent) : QObject(parent)
{
    initSocket();
}

CommModule* CommModule::getInstance()
{
    if(commModule == NULL){
        commModule = new CommModule();
    }
    return commModule;
}

void CommModule::initSocket()
{
    emit logModule->log("init socket");
    commSocket = new QUdpSocket(this);
    commSocket->bind(QHostAddress::Any,SVR_PORT);
    connect(commSocket,SIGNAL(readyRead()),
            this,SLOT(readClient()));
}

void CommModule::readClient()
{
    QByteArray datagram;

    while(commSocket->hasPendingDatagrams()){
        QHostAddress *clientAddr = new QHostAddress();
        emit logModule->log("comm module read client:"+
                            QString::number(commSocket->pendingDatagramSize()));
        datagram.resize(commSocket->pendingDatagramSize());
        commSocket->readDatagram(datagram.data(),datagram.size(),clientAddr);
        QTextCodec *utf8codec = QTextCodec::codecForName("UTF-8");
        QString utf8str = utf8codec->toUnicode(datagram);
        datagram = utf8str.toStdString().data();

        emit getNewRequest(*clientAddr,datagram);
    }
}

void CommModule::sendData(QHostAddress cAddr,QJsonObject data)
{
    QJsonDocument jd;
    jd.setObject(data);
    commSocket->writeDatagram(jd.toJson(),cAddr,CLIENT_PORT);
}

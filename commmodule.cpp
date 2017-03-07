#include "commmodule.h"

CommModule * CommModule::commModule = NULL;

CommModule *CommModule::getInstance()
{
    if(commModule == NULL){
        commModule = new CommModule();
    }
    return commModule;
}

CommModule::~CommModule()
{
    delete commModule;
    delete commSocket;
}

CommModule::CommModule(QObject *parent) : QObject(parent)
{
    initSocket();
    qDebug()<<"CommModule thread id:"<<QThread::currentThreadId();
}

void CommModule::initSocket()
{
    commSocket = new QUdpSocket(this);
    commSocket->bind(QHostAddress::Any,SVR_PORT);
    connect(commSocket,SIGNAL(readyRead()),
            this,SLOT(readClient()));
}

void CommModule::readClient()
{
    QByteArray datagram;
    while(commSocket->hasPendingDatagrams()){
        emit logModule->log("comm module read client");
        datagram.resize(commSocket->pendingDatagramSize());
        commSocket->readDatagram(datagram.data(),datagram.size());
        QString cIp = commSocket->peerAddress().toString();
        emit getNewRequest(cIp,datagram);
    }
}

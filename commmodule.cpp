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
        datagram.resize(commSocket->pendingDatagramSize());
        commSocket->readDatagram(datagram.data(),datagram.size());
        emit getNewRequest(datagram);
    }
}

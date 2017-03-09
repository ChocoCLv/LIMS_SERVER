#include "commmodule.h"

CommModule::~CommModule()
{
    delete commSocket;
}

CommModule::CommModule(QObject *parent) : QObject(parent)
{
    initSocket();
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
        emit logModule->log("comm module read client");
        datagram.resize(commSocket->pendingDatagramSize());
        commSocket->readDatagram(datagram.data(),datagram.size());
        QString cIp = commSocket->peerAddress().toString();
        emit getNewRequest(cIp,datagram);
    }
}

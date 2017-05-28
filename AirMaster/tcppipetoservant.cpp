#include "tcppipetoservant.h"

TcpPipeToServant::TcpPipeToServant(QObject *parent, QTcpSocket *_clientTcp)
    : QObject(parent),clientTcp(_clientTcp)
{
    connect(clientTcp,SIGNAL(readyRead()),this,SLOT(readPacket()));
}

void TcpPipeToServant::setClientTcp(QTcpSocket *value)
{
    clientTcp = value;
}

void TcpPipeToServant::readPacket()
{
    QString receiveStr=clientTcp->readAll();
    qDebug()<<receiveStr;
}

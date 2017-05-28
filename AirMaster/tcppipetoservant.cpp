#include "tcppipetoservant.h"

TcpPipeToServant::TcpPipeToServant(QObject *parent, QTcpSocket *_clientTcp, PacketHandler *handler)
    : QObject(parent),clientTcp(_clientTcp),packetHandler(handler)
{
    connect(clientTcp,SIGNAL(readyRead()),this,SLOT(readPacket()));
}

TcpPipeToServant::~TcpPipeToServant()
{

}

void TcpPipeToServant::setClientTcp(QTcpSocket *value)
{
    clientTcp = value;
}

void TcpPipeToServant::readPacket()
{
    QString receiveStr=clientTcp->readAll();
    std::string pack=receiveStr.toStdString();
    std::string sendStr=packetHandler->handlePacketStr(pack);
    clientTcp->write(sendStr.c_str());
    qDebug()<<receiveStr;
}

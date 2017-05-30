#include "tcppipetoservant.h"

TcpPipeToServant::TcpPipeToServant(QObject *parent, QTcpSocket *_clientTcp)
    : QObject(parent),clientTcp(_clientTcp)
{
    ip=clientTcp->peerAddress().toString().toStdString();
    port=clientTcp->peerPort();
//    firstTemperature=true;
    connect(clientTcp,SIGNAL(readyRead()),this,SLOT(readPacket()));
}

TcpPipeToServant::~TcpPipeToServant()
{

}

void TcpPipeToServant::sendFreshPeriod()
{
    examinePackHandler();
    std::string sendStr=packetHandler->constructSendPack("freshperiod");
    clientTcp->write(sendStr.c_str());
}

void TcpPipeToServant::setClientTcp(QTcpSocket *value)
{
    clientTcp = value;
}

void TcpPipeToServant::examinePackHandler()
{
   if(!packetHandler)
       throw "PacketHandler can't be nullptr";

}

void TcpPipeToServant::readPacket()
{
    QString receiveStr=clientTcp->readAll();
    std::string pack=receiveStr.toStdString();
    std::string packType=getJsonStrType(pack);
    if(packType=="temp"||packType=="auth")
    {
        examinePackHandler();
        std::string sendStr=packetHandler->handlePacketStr(pack);
        clientTcp->write(sendStr.c_str());
    }
    else
    {

//        attachQueueHelper();
    }
    qDebug()<<receiveStr;
}

int TcpPipeToServant::getRequestCacheCounter() const
{
    return requestCacheCounter;
}

void TcpPipeToServant::setPacketHandler(PacketHandler *value)
{
    packetHandler = value;
}

void TcpPipeToServant::addRequestCache(std::string res)
{
   requestCache.push(res);
   requestCacheCounter++;
}

std::string TcpPipeToServant::popRequestCache()
{
    std::string res;
    if(!requestCache.empty())
    {
        res=requestCache.front();
        requestCache.pop();
        requestCacheCounter--;
    }
    return res;
}

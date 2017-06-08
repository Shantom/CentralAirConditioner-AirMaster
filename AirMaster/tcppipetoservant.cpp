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
//    examinePackHandler();
    std::string sendStr=packetHandler->constructSendPack("freshperiod");
    clientTcp->write(sendStr.c_str());
}

void TcpPipeToServant::sendWorkingState()
{
    std::string sendStr = packetHandler->constructSendPack("workingstate");
    clientTcp->write(sendStr.c_str());
}

void TcpPipeToServant::sendWind(std::string wind_velocity)
{
    std::string sendStr = packetHandler->constructSendWind(wind_velocity);
    clientTcp->write(sendStr.c_str());
}

void TcpPipeToServant::setClientTcp(QTcpSocket *value)
{
    clientTcp = value;
}


void TcpPipeToServant::readPacket()
{
    QString receiveStr=clientTcp->readAll();
    std::string pack=receiveStr.toStdString();
    PACKET_TYPE packType=getJsonStrType(pack);
    if(packType== TEMP_PACKET)
    {
        AirPacket* tempPacket=new TemperatureClient(pack);
        addRequestCache(tempPacket);
//        std::string sendStr=packetHandler->handlePacketStr(pack);
 //       clientTcp->write(sendStr.c_str());
    }
    else if(packType==AUTH_PACKET)
    {
        AirPacket* authPacket=new AuthClient(pack);
        addRequestCache(authPacket);
//        std::string sendStr=packetHandler->handlePacketStr(pack);
//        clientTcp->write(sendStr.c_str());
    }
    else if (packType == START_WIND_PACKET)
    {
        AirPacket* startWindPacket=new StartWindClient(pack);
        qDebug()<<reinterpret_cast<StartWindClient*>(startWindPacket)->velocity.c_str();
        addRequestCache(startWindPacket);
//        attachQueueHelper();
    }
    else if(packType == STOP_WIND_PACKET)
    {
        AirPacket* stopWind=new StopWindClient(pack);
        addRequestCache(stopWind);
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

void TcpPipeToServant::addRequestCache(AirPacket* res)
{
   requestCache.push(res);
   requestCacheCounter++;
}

AirPacket* TcpPipeToServant::popRequestCache()
{
    AirPacket* res;
    if(!requestCache.empty())
    {
        res=requestCache.front();
        requestCache.pop();
        requestCacheCounter--;
    }
    return res;
}

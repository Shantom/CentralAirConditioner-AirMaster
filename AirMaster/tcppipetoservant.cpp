#include "tcppipetoservant.h"

TcpPipeToServant::TcpPipeToServant(QObject *parent, QTcpSocket *_clientTcp)
    : QObject(parent),clientTcp(_clientTcp),receiveStr("")
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
    QString receiveNewStr=clientTcp->readAll();
    receiveStr += receiveNewStr.toStdString();
    std::vector<std::string> allJsons = parseJsonStr(receiveStr);

    for(auto &pack :allJsons){
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
//            qDebug()<<reinterpret_cast<StartWindClient*>(startWindPacket)->velocity.c_str();
            addRequestCache(startWindPacket);
            //        attachQueueHelper();
        }
        else if(packType == STOP_WIND_PACKET)
        {
            AirPacket* stopWind=new StopWindClient(pack);
            addRequestCache(stopWind);
        }

    }

}

std::vector<std::string> TcpPipeToServant::parseJsonStr(std::string &originStr)
{
    std::vector<std::string> allJsons;
    std::string oneJson = parseOneJson(originStr);
    while(!oneJson.empty()){
         allJsons.push_back(oneJson);
         oneJson = parseOneJson(originStr);
    }
    return allJsons;
}

std::string TcpPipeToServant::parseOneJson(std::string &originStr)
{
    int leftCounter=0,flag=0,rightCounter=0;
    while(flag < originStr.size()){
        if(originStr[flag] == '{'){
            leftCounter++;
        }
        if (originStr[flag] == '}'){
            rightCounter++;
            if (rightCounter == leftCounter){
                std::string res = originStr.substr(0,flag+1);
                originStr=originStr.substr(flag+1,originStr.size()-flag);
                return res;
            }
        }
        flag++;
    }
    return "";
}

int TcpPipeToServant::getRequestCacheCounter() const
{
    if (requestCacheCounter <= 0){
        return 0;
    }
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
    AirPacket* res = nullptr;
    if(!requestCache.empty())
    {
        res=requestCache.front();
        requestCache.pop();
        requestCacheCounter = requestCache.size();
    }
    return res;
}

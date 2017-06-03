#include "packethandler.h"


PacketHandler::PacketHandler(AirConditionMaster &_airMaster)
    :airMaster(_airMaster)
{

}

std::string PacketHandler::handlePacketStr(std::string &str)
{
//    std::string typeStr=getJsonStrType(str);
//    if(typeStr=="temp")
//    {
//        FreshRateServer tc=FreshRateServer(airMaster.getFreshperiod());
//        qDebug()<<tc.toJsonStr().c_str();
//        return tc.toJsonStr();
//    }
//    else if(typeStr=="auth")
//    {
//        WorkStateServer ac=WorkStateServer(airMaster.getCurrentModeStr(),airMaster.getDefaTemperature());
//        qDebug()<<ac.toJsonStr().c_str();
//        return ac.toJsonStr();
//   }
    return "";

}

std::string PacketHandler::constructSendPack(std::string packetType)
{
    if(packetType=="freshperiod")
    {
        FreshRateServer tc=FreshRateServer(airMaster.getFreshperiod());
        qDebug()<<tc.toJsonStr().c_str();
        return tc.toJsonStr();
    }
}

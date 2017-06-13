#include "packethandler.h"


PacketHandler::PacketHandler(AirConditionMaster &_airMaster)
    :airMaster(_airMaster)
{

}

//std::string PacketHandler::handlePacketStr(std::string &str)
//{
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
//    return "";

//}

std::string PacketHandler::constructSendPack(std::string packetType)
{
    if(packetType=="freshperiod")
    {
        FreshRateServer tc=FreshRateServer(airMaster.getFreshperiod());
        qDebug()<<">>"<<tc.toJsonStr().c_str();
        return tc.toJsonStr();
    }
    else if (packetType == "workingstate"){
        WorkStateServer ws = WorkStateServer(airMaster.getCurrentModeStr(),airMaster.getDefaTemperature());
        qDebug()<<">>"<<ws.toJsonStr().c_str();
        return ws.toJsonStr();
    }

}

std::string PacketHandler::constructSendWind(std::string velocity)
{
   SendWindServer ss = SendWindServer(airMaster.getDefaTemperature(),velocity);
   qDebug()<<">>"<<ss.toJsonStr().c_str();
   return ss.toJsonStr();
}

std::string PacketHandler::constructSendFee(float fee, float kwh)
{
    CountFeeServer cs = CountFeeServer(kwh,fee);
    qDebug()<<">>"<<cs.toJsonStr().c_str();
    return cs.toJsonStr();
}

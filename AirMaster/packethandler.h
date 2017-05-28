#ifndef PACKETHANDLER_H
#define PACKETHANDLER_H

#include"json.hpp"
#include"airpacket.h"
#include "airconditionmaster.h"

using json=nlohmann::json;
class PacketHandler
{
public:
    PacketHandler(AirConditionMaster& _airMaster);
    std::string handlePacketStr(std::string& str);
private:
    AirConditionMaster &airMaster;
    // FeeCounter
    // reportGenerator
};

#endif // PACKETHANDLER_H

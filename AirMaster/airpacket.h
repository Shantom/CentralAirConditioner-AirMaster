#ifndef AIRPACKET_H
#define AIRPACKET_H

#include<string>
#include"json.hpp"
#include"aircommon.h"
#include <map>
using json=nlohmann::json;

enum PACKET_TYPE{TEMP_PACKET=1,AUTH_PACKET=2,START_WIND_PACKET=3,STOP_WIND_PACKET=4,
                 FRESHRATE_PACKET=5,WORK_STATE_PACKET=6,COUNT_FEE_PACKET=7,SEND_WIND_PACKET=8,ERROR_PACKET=9};

static std::map<std::string,PACKET_TYPE> typeMap{{"temp",TEMP_PACKET},{"auth",AUTH_PACKET},{"startwind",START_WIND_PACKET},
                                         {"stopwind",STOP_WIND_PACKET},{"freshrate",FRESHRATE_PACKET},{"mode",WORK_STATE_PACKET},
                                         {"bill",COUNT_FEE_PACKET},{"wind",SEND_WIND_PACKET}};
class AirPacket
{

public:
    AirPacket();
    virtual std::string toJsonStr()=0;
    virtual PACKET_TYPE  getType()=0;
    std::string sourceIp;
    int sourcePort;
};

class TemperatureClient: public AirPacket
{
public:
    TemperatureClient(int _temp);
    TemperatureClient(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    int temp;
};

class AuthClient:public AirPacket
{
public:
    AuthClient(std::string _room,std::string _id);
    AuthClient(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    std::string room;
    std::string id;
};

class StartWindClient:public AirPacket
{
public:
    StartWindClient(int _desttemp,std::string _velocity);
    StartWindClient(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    int desttemp;
    int velocity;
};

class StopWindClient:public AirPacket
{
public:
    StopWindClient();
    StopWindClient(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();


};

class FreshRateServer:public AirPacket
{
public:
    FreshRateServer(int _freshperiod);
    FreshRateServer(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    int freshperiod;
};

class WorkStateServer:public AirPacket
{
public:
    WorkStateServer(std::string _workingmode,int _deftemp);
    WorkStateServer(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    std::string workingmode;
    int defaulttemp;
};

class CountFeeServer:public AirPacket
{
public:
    CountFeeServer(float kwh,float bill);
    CountFeeServer(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    float kwh;
    float bill;
};

class SendWindServer:public AirPacket
{
public:
    SendWindServer(int windtemp,std::string velocity);
    SendWindServer(std::string& packet);
    std::string toJsonStr();
    PACKET_TYPE  getType();
    int windtemp;
    std::string velocity;
};


// util funciton for AirPacket
PACKET_TYPE getJsonStrType(std::string& str);

#endif // AIRPACKET_H

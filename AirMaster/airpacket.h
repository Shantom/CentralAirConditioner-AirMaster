#ifndef AIRPACKET_H
#define AIRPACKET_H

#include<string>
#include"json.hpp"
#include"aircommon.h"

using json=nlohmann::json;

class AirPacket
{
public:
    AirPacket();
    virtual std::string toJsonStr()=0;

private:
    std::string sourceIp;
    int sourcePort;
};

class TemperatureClient:AirPacket
{
public:
    TemperatureClient(int _temp);
    TemperatureClient(std::string& packet);
    std::string toJsonStr();
private:
    int temp;
};

class AuthClient:AirPacket
{
public:
    AuthClient(std::string _room,std::string _id);
    AuthClient(std::string& packet);
    std::string toJsonStr();
private:
    std::string room;
    std::string id;
};

class StartWindClient:AirPacket
{
public:
    StartWindClient(int _desttemp,std::string _velocity);
    StartWindClient(std::string& packet);
    std::string toJsonStr();
private:
    int desttemp;
    int velocity;
};

class StopWindClient:AirPacket
{
public:
    StopWindClient();
    StopWindClient(std::string& packet);
    std::string toJsonStr();
private:

};

class FreshRateServer:AirPacket
{
public:
    FreshRateServer(int _freshperiod);
    FreshRateServer(std::string& packet);
    std::string toJsonStr();
private:
    int freshperiod;
};

class WorkStateServer:AirPacket
{
public:
    WorkStateServer(std::string _workingmode,int _deftemp);
    WorkStateServer(std::string& packet);
    std::string toJsonStr();
private:
    std::string workingmode;
    int defaulttemp;
};

class CountFeeServer:AirPacket
{
public:
    CountFeeServer(float kwh,float bill);
    CountFeeServer(std::string& packet);
    std::string toJsonStr();
private:
    float kwh;
    float bill;
};

class SendWindServer:AirPacket
{
public:
    SendWindServer(int windtemp,std::string velocity);
    SendWindServer(std::string& packet);
    std::string toJsonStr();
private:
    int windtemp;
    std::string velocity;
};



#endif // AIRPACKET_H

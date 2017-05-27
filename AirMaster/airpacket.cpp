#include "airpacket.h"

AirPacket::AirPacket()
{

}

TemperatureClient::TemperatureClient(int _temp)
    :temp(_temp)
{

}

TemperatureClient::TemperatureClient(std::string& packet)
{

    lowerStr(packet);
    json pac=json::parse(packet);
    temp=pac["temp"];

}

std::string TemperatureClient::toJsonStr()
{
    json pac;
    pac["type"]="temp";
    pac["temp"]=temp;
    return pac.dump();
}

AuthClient::AuthClient(std::string _room, std::string _id)
    :room(_room),id(_id)
{

}

AuthClient::AuthClient(std::string& packet)
{

    lowerStr(packet);
    json pac=json::parse(packet);
    room=pac["room"];
    id=pac["id"];

}

std::string AuthClient::toJsonStr()
{
    json pac;
    pac["type"]="auth";
    pac["room"]=room;
    pac["id"]=id;
    return pac.dump();
}

StartWindClient::StartWindClient(int _desttemp, std::string _velocity)
    :desttemp(_desttemp),velocity(_desttemp)
{

}

StartWindClient::StartWindClient(std::string& packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
    desttemp=pac["desttemp"];
}

std::string StartWindClient::toJsonStr()
{
    json pac;
    pac["type"]="startwind";
    pac["desttemp"]=desttemp;
    pac["velocity"]=velocity;
    return pac.dump();
}

StopWindClient::StopWindClient()
{

}

StopWindClient::StopWindClient(std::string& packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
}

std::string StopWindClient::toJsonStr()
{
    json pac;
    pac["type"]="stopwind";
    return pac.dump();
}

FreshRateServer::FreshRateServer(int _freshperiod)
    :freshperiod(_freshperiod)
{

}

FreshRateServer::FreshRateServer(std::string& packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
    freshperiod=pac["freshperiod"];
}

std::string FreshRateServer::toJsonStr()
{
    json pac;
    pac["type"]="freshrate";
    pac["freshperiod"]=freshperiod;
    return pac.dump();
}

SendWindServer::SendWindServer(int windtemp, std::string velocity)
    :windtemp(windtemp),velocity(velocity)
{

}

SendWindServer::SendWindServer(std::string& packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
    windtemp=pac["windtemp"];
    velocity=pac["velocity"];
}

std::string SendWindServer::toJsonStr()
{
    json pac;
    pac["type"]="wind";
    pac["windtemp"]=windtemp;
    pac["velocity"]=velocity;
    return pac.dump();
}

WorkStateServer::WorkStateServer(std::string _workingmode, int _deftemp)
    :workingmode(_workingmode),defaulttemp(_deftemp)
{

}

WorkStateServer::WorkStateServer(std::string& packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
    workingmode=pac["workingmdoe"];
    defaulttemp=pac["defaulttemp"];
}

std::string WorkStateServer::toJsonStr()
{
    json pac;
    pac["type"]="mode";
    pac["workingmode"]=workingmode;
    pac["defaulttemp"]=defaulttemp;
    return pac.dump();
}

CountFeeServer::CountFeeServer(float kwh, float bill)
    :kwh(kwh),bill(bill)
{

}

CountFeeServer::CountFeeServer(std::string &packet)
{
    lowerStr(packet);
    json pac=json::parse(packet);
    kwh=pac["kwh"];
    bill=pac["bill"];
}

std::string CountFeeServer::toJsonStr()
{
    json pac;
    pac["type"]="bill";
    pac["kwh"]=kwh;
    pac["bill"]=bill;
    return pac.dump();
}

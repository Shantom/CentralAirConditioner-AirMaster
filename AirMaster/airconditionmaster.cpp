#include "airconditionmaster.h"

AirConditionMaster::AirConditionMaster()
{
    initMaster();
}

void AirConditionMaster::initMaster()
{
    freshperiod=1;
    defaTemperature=22;
    currentMode=COLD;
}

void AirConditionMaster::setCurrentMode(const WORK_MODE &value)
{
    currentMode = value;
}

int AirConditionMaster::getFreshperiod() const
{
    return freshperiod;
}

int AirConditionMaster::getDefaTemperature() const
{
    return defaTemperature;
}

std::string AirConditionMaster::getCurrentModeStr() const
{
    return currentMode==WORK_MODE::COLD ? "COLD":"HOT";
}

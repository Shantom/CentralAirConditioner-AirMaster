#include "airconditionmaster.h"

AirConditionMaster::AirConditionMaster()
{

}

void AirConditionMaster::setDefaTemperature(float value)
{
    defaTemperature = value;
}

void AirConditionMaster::setCurrentMode(const WORK_MODE &value)
{
    currentMode = value;
}

#ifndef AIRCONDITIONMASTER_H
#define AIRCONDITIONMASTER_H

#include <airencrypter.h>
#include <loginairmaster.h>
#include <aircommon.h>

class AirConditionMaster
{
public:
    enum WORK_MODE{COLD,HOT};
    AirConditionMaster();

    void setDefaTemperature(float value);
    void setCurrentMode(const WORK_MODE &value);

private:
    WORK_MODE currentMode;
    float defaTemperature;
    std::string curVelocity;
};

#endif // AIRCONDITIONMASTER_H

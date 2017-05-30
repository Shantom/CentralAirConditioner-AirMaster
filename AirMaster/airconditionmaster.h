#ifndef AIRCONDITIONMASTER_H
#define AIRCONDITIONMASTER_H

#include <airencrypter.h>
#include <loginairmaster.h>
#include <aircommon.h>
#include <map>
class AirConditionMaster
{
public:
    enum WORK_MODE{COLD,HOT};
    AirConditionMaster();

    void initMaster();
    void setCurrentMode(const WORK_MODE &value);

    int getFreshperiod() const;

    int getDefaTemperature() const;

    std::string getCurrentModeStr() const;

private:
    std::map<std::string,bool> isFirstTemperature;

    WORK_MODE currentMode;
    int defaTemperature;
    std::string curVelocity;
    int freshperiod;
};

#endif // AIRCONDITIONMASTER_H

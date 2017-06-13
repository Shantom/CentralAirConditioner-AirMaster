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
    void setFreshperiod(const int& value){freshperiod=value;}

    int getDefaTemperature() const;
    void setDefaTemperature(const int& value){defaTemperature=value;}

    std::string getCurrentModeStr() const;
    void setCurrentModeStr(const std::string& value)
    {currentMode=value=="COLD"?COLD:HOT;}

private:
    std::map<std::string,bool> isFirstTemperature;

    WORK_MODE currentMode;
    int defaTemperature;
    std::string curVelocity;
    int freshperiod;
};

#endif // AIRCONDITIONMASTER_H

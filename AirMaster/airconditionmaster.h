#ifndef AIRCONDITIONMASTER_H
#define AIRCONDITIONMASTER_H

#include <airencrypter.h>
#include <loginairmaster.h>

class AirConditionMaster
{
public:
    enum WORK_MODE{COLD,HOT};
    AirConditionMaster();
private:
    WORK_MODE currentMode;
    float defaTemperature;


    LoginAirMaster loginHandler;
};

#endif // AIRCONDITIONMASTER_H

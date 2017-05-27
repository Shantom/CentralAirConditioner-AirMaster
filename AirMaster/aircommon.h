#ifndef AIRCOMMON_H
#define AIRCOMMON_H

#include<string>
#include<cwctype>
enum wind_velocity{
    wind_high=1,wind_medium=2,wind_low=3,wind_none=4
};

enum work_mode{
    mode_hot=1,mode_cold=2
};


void lowerStr(std::string& str);

#endif // AIRCOMMON_H

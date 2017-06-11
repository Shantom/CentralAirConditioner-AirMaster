#ifndef AIRCOMMON_H
#define AIRCOMMON_H

#include<string>
#include<cwctype>

typedef struct RequestInfo{
    std::string roomId;
    std::string start_time;
    std::string end_time;
    int start_temperature;
    int end_temperature;
    float fee;
    std::string velocity;
    bool complete;   // info is done or not
}RequestInfo,*pRequestInfo;


enum wind_velocity{
    wind_high=1,wind_medium=2,wind_low=3,wind_none=4
};

enum work_mode{
    mode_hot=1,mode_cold=2
};


void lowerStr(std::string& str);

#endif // AIRCOMMON_H

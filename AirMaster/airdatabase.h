#ifndef AIRDATABASE_H
#define AIRDATABASE_H
#include <QDebug>
#include <hiredis/hiredis.h>
#include <aircommon.h>

class AirDatabase
{
public:
    AirDatabase();
    ~AirDatabase();
    bool connectDatabase(std::string address,int port);
    void addRequestInfo(pRequestInfo requestInfo);
    void setSwitchTimes(int switch_times);

private:
    redisContext *connector;
    unsigned int maxRequestNum;

};

#endif // AIRDATABASE_H

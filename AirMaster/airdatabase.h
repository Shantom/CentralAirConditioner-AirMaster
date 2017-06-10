#ifndef AIRDATABASE_H
#define AIRDATABASE_H
#include <QDebug>
#include <hiredis/hiredis.h>
#include <aircommon.h>

class AirDatabase
{
public:
    AirDatabase();
    bool connectDatabase(std::string address,int port);
    void setSwitchTimes(int switch_times);

private:
    redisContext *connector;

};

#endif // AIRDATABASE_H

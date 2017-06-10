#ifndef AIRDATABASE_H
#define AIRDATABASE_H
#include <QDebug>
#include <hiredis/hiredis.h>

class AirDatabase
{
public:
    AirDatabase();
    bool connectDatabase(std::string address,int port);

private:
    redisContext *connector;

};

#endif // AIRDATABASE_H

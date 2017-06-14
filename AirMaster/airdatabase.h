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

    void initAllRequests(std::map<std::string, std::vector<pRequestInfo>>& allCompleteRequests);
private:
    redisContext *connector;
    std::map<std::string, int> allRequestNums;
};

#endif // AIRDATABASE_H

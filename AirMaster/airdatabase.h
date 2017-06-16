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
    void updateSwitchTime(std::string room,int times);
    void initSwitchTimes(std::vector<std::string> & allRoomsId,std::map<std::string, int> & allSwitchTimes);

    void initAllRequests(std::map<std::string, std::vector<pRequestInfo> > &allCompleteRequests
                                      ,std::map<std::string, int> &allSwitchTimes);

    bool checkUserId(std::string roomId, std::string userId);


private:
    redisContext *connector;
    std::map<std::string, int> allRequestNums;
};

#endif // AIRDATABASE_H

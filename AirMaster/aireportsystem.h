#ifndef AIREPORTSYSTEM_H
#define AIREPORTSYSTEM_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <aircommon.h>
#include "airdatabase.h"


class AiReportSystem
{
public:
    AiReportSystem();

    // sync with database
    void syncDatabase();

    // this uncomplete requestInfo will be added into cache
    void addNewRequestInfo(pRequestInfo newResquest);

    // get some room's last uncomplete RequestInfo
    pRequestInfo getRoomRequestInfo(std::string roomId);

    // request stop, update and fill a complete requestinfo
    void updateRequestComplete(pRequestInfo completeRequestInfo);

    void updateSwitchTimes(std::string room);
    std::map<std::string, std::vector<pRequestInfo>>* getAllCompleteRequests()
    {return &allCompleteRequests;}

    int getSwitchTime(std::string room){return allSwitchTimes[room];}
private:
    // cached uncomplete RequestInfo
    std::map<std::string, pRequestInfo> allCachedRequests;

    // key is roomId, value is its ReqeustInfos
    std::map<std::string, std::vector<pRequestInfo>> allCompleteRequests;
    std::map<std::string, int> allSwitchTimes;

    AirDatabase *airDatabase;
};

#endif // AIREPORTSYSTEM_H

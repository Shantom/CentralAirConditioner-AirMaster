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

private:

    // cached uncomplete RequestInfo
     std::map<std::string, pRequestInfo> allCachedRequests;

    // key is roomId, value is its ReqeustInfos
    std::map<std::string, std::vector<pRequestInfo>> allCompleteRequests;
};

#endif // AIREPORTSYSTEM_H

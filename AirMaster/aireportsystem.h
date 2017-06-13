#ifndef AIREPORTSYSTEM_H
#define AIREPORTSYSTEM_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include <aircommon.h>


class AiReportSystem
{
public:
    AiReportSystem();

    // sync with database
    void syncDatabase();
private:

    std::string currentTimeStamp();


    // cached uncomplete RequestInfo
    std::list<pRequestInfo> allCachedRequests;

    // key is roomId, value is its ReqeustInfos
    std::map<std::string, std::vector<pRequestInfo>> allCompleteRequests;
};

#endif // AIREPORTSYSTEM_H

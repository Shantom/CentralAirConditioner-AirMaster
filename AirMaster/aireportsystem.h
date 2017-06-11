#ifndef AIREPORTSYSTEM_H
#define AIREPORTSYSTEM_H

#include <string>
#include <list>
#include <aircommon.h>


class AiReportSystem
{
public:
    AiReportSystem();

    // sync with database
    void syncDatabase();
private:
//    std::list<pRequestInfo> allRequestsLog;
};

#endif // AIREPORTSYSTEM_H

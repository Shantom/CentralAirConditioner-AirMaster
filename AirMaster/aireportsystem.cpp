#include "aireportsystem.h"

AiReportSystem::AiReportSystem()
{
    airDatabase = new AirDatabase();
    airDatabase->connectDatabase("127.0.0.1",6379);
    airDatabase->initAllRequests(allCompleteRequests,allSwitchTimes);

}

void AiReportSystem::syncDatabase()
{

}

void AiReportSystem::addNewRequestInfo(pRequestInfo newResquest)
{
    allCachedRequests[newResquest->roomId]=newResquest;
}

pRequestInfo AiReportSystem::getRoomRequestInfo(std::string roomId)
{
    return allCachedRequests[roomId];
}

void AiReportSystem::updateRequestComplete(pRequestInfo completeRequestInfo)
{
    allCachedRequests[completeRequestInfo->roomId]=nullptr;
    allCompleteRequests[completeRequestInfo->roomId].push_back(completeRequestInfo);

    airDatabase->addRequestInfo(completeRequestInfo);

}

void AiReportSystem::updateSwitchTimes(std::string room)
{
   allSwitchTimes[room]++;
   airDatabase->updateSwitchTime(room,allSwitchTimes[room]);
   std::string te= room+" switch times : "+std::to_string(allSwitchTimes[room]);
   qDebug()<<te.c_str();
}

#include "aireportsystem.h"

AiReportSystem::AiReportSystem()
{
    airDatabase = new AirDatabase();
    airDatabase->connectDatabase("127.0.0.1",6379);

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

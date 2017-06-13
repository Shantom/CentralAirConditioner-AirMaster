#include "aireportsystem.h"

AiReportSystem::AiReportSystem()
{

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

}

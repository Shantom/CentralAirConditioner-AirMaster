#include "airdatabase.h"

AirDatabase::AirDatabase()
{

}

AirDatabase::~AirDatabase()
{
    redisFree(connector);
}

bool AirDatabase::connectDatabase(std::string address, int port)
{
   connector = redisConnect(address.c_str(),port);
   if (connector == nullptr || connector->err){
       if (connector){
          qDebug()<<connector->errstr;
       }
       else{
           qDebug()<<"can't allocate redis context";
       }
       return false;
   }
   qDebug()<<"connect successfully";

   // init maxRequestNum
   return true;
}

void AirDatabase::addRequestInfo(pRequestInfo requestInfo)
{
   std::string command;
   command += (requestInfo->roomId + ":");
   command += "allRequests:";
   command += std::to_string(maxRequestNum+1);
   command += " ";

   command += ("start_time "+requestInfo->start_time+" ");
   command += ("end_time "+ requestInfo->end_time+" ");
   command += ("start_temperature "+std::to_string(requestInfo->start_temperature)+" ");
   command += ("end_temperature "+std::to_string(requestInfo->end_temperature)+" ");
   command += ("velocity "+requestInfo->velocity);
   command += ("fee "+ std::to_string(requestInfo->fee));

   // add error handle
    redisCommand(connector,command.c_str());

}


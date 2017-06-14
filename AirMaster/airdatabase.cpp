#include "airdatabase.h"

AirDatabase::AirDatabase():maxRequestNum(0)
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
   command += "HMSET ";
   command += (requestInfo->roomId + ":");
   command += "allRequests:";
   command += std::to_string(maxRequestNum++);
   command += " ";

   command += ("start_time "+requestInfo->start_time+" ");
   command += ("end_time "+ requestInfo->end_time+" ");
   command += ("start_temperature "+std::to_string(requestInfo->start_temperature)+" ");
   command += ("end_temperature "+std::to_string(requestInfo->end_temperature)+" ");
   command += ("velocity "+requestInfo->velocity+" ");
   command += ("fee "+ std::to_string(requestInfo->fee));

   qDebug()<<"command: "<<command.c_str();
   // add error handle
    redisCommand(connector,command.c_str());

    // update maxRequestNum
    command.clear();
    command += ("hmset "+requestInfo->roomId + " maxRequestNum "+std::to_string(maxRequestNum));
    redisCommand(connector,command.c_str());

}


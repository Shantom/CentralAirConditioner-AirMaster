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
   return true;
}

void AirDatabase::addRequestInfo(pRequestInfo requestInfo)
{
   std::string command;
   command += "HMSET ";
   command += (requestInfo->roomId + ":");
   command += "allRequests:";
   command += std::to_string(allRequestNums[requestInfo->roomId]++);
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
    command += ("hmset "+requestInfo->roomId + " maxRequestNum "+std::to_string(allRequestNums[requestInfo->roomId]));
    redisCommand(connector,command.c_str());

    // add roomId to allRooms
    command.clear();
    command += ("sadd allRooms "+requestInfo->roomId);
    redisCommand(connector,command.c_str());
}

void AirDatabase::initAllRequests(std::map<std::string, std::vector<pRequestInfo> > &allCompleteRequests)
{
    // get all rooms Id in database
    std::string command;
    command += "scard allRooms ";
    redisReply* reply;
    reply= reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
    int roomNum = reply->integer;
    freeReplyObject(reply);

    // no history rooms reports and return
    if (roomNum == 0){
        return;
    }

    command.clear();
    command += "smembers allRooms ";
    reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));

    std::vector<std::string> allRoomsId;
    for(int i=0; i<reply->elements ; i++){
        allRoomsId.push_back(std::string(reply->element[i]->str));
    }
    freeReplyObject(reply);


    // init all RequestNums
    for (auto& room:allRoomsId){
        command.clear();
        command += ("hmget "+room+" maxRequestNum ");
        reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
        allRequestNums[room] = reply->integer;
        freeReplyObject(reply);
    }


    for (auto& room:allRoomsId){
        for(int i =1 ; i< allRequestNums[room]+1; i++){
            pRequestInfo requestIn = reinterpret_cast<pRequestInfo>(new pRequestInfo());
            requestIn->roomId = room;

            std::string basicStr = ("hmget "+room+":allRequests:"+std::to_string(i));

            command.clear();
            command += (basicStr + " start_time");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->start_time = std::string(reply->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " end_time");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->end_time= std::string(reply->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " velocity ");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->velocity= std::string(reply->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " start_temperature");
            reply =reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->start_temperature = reply->integer;
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " end_temperature");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->end_temperature = reply->integer;
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " fee");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->fee = reply->integer;
            freeReplyObject(reply);
        }

    }


}


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

void AirDatabase::updateSwitchTime(std::string room, int times)
{
    std::string command;
    command += ("hmset " +room+"  switch_times "+std::to_string(times));
    redisCommand(connector,command.c_str());
}

void AirDatabase::initSwitchTimes(std::vector<std::string> & allRoomsId,std::map<std::string, int> &allSwitchTimes)
{
   redisReply* reply;
   std::string command;
   for(auto & room :allRoomsId){
       command.clear();
       command +=("hmget "+room+" switch_times ");
       reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
       if (reply->element[0]->str){
           allSwitchTimes[room] =std::stoi(reply->element[0]->str);
       }
       freeReplyObject(reply);
   }
}

void AirDatabase::initAllRequests(std::map<std::string, std::vector<pRequestInfo> > &allCompleteRequests
                                  ,std::map<std::string, int> &allSwitchTimes)
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
        qDebug()<< reply->str;
        allRequestNums[room] = std::stoi(std::string(reply->element[0]->str));
        freeReplyObject(reply);
    }

    initSwitchTimes(allRoomsId,allSwitchTimes);

    for (auto& room:allRoomsId){
        for(int i = 0 ; i< allRequestNums[room]; i++){
            pRequestInfo requestIn = reinterpret_cast<pRequestInfo>(new RequestInfo());
            requestIn->roomId = room;

            std::string basicStr = ("hmget "+room+":allRequests:"+std::to_string(i));

            command.clear();
            command += (basicStr + " start_time");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->start_time =std::string(reply->element[0]->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " end_time");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->end_time= std::string(reply->element[0]->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " velocity ");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->velocity= std::string(reply->element[0]->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " start_temperature");
            reply =reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->start_temperature = std::stoi(reply->element[0]->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " end_temperature");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->end_temperature =std::stoi(reply->element[0]->str);
            freeReplyObject(reply);

            command.clear();
            command += (basicStr + " fee");
            reply = reinterpret_cast<redisReply*>(redisCommand(connector,command.c_str()));
            requestIn->fee = std::stof(reply->element[0]->str);
            freeReplyObject(reply);

            allCompleteRequests[room].push_back(requestIn);
        }

    }


}

bool AirDatabase::checkUserId(std::string roomId,std::string userId)
{

}


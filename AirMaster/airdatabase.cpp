#include "airdatabase.h"

AirDatabase::AirDatabase()
{

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


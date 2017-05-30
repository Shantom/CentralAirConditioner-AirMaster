#include "resqueuehandler.h"

ResQueueHandler::ResQueueHandler(PacketHandler *packHandler)
    :packetHandler(packHandler)
{

}

void ResQueueHandler::startPacketMonitor()
{
    //monitorPacket=new std::thread(monitoringServant);
    //monitorPacket.join();
}

void ResQueueHandler::monitoringServant()
{

    while(true)
    {
       for(auto &cl:allClients)
       {
          if(cl->getRequestCacheCounter()>0)
              //collect packet which need handling;
              ;
       }
    }
}

void ResQueueHandler::initQueueHandler()
{

}

void ResQueueHandler::addTcpServant(TcpPipeToServant *servant)
{
    allClients.push_back(servant);
    servant->setPacketHandler(packetHandler);
}

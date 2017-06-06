#include "resqueuehandler.h"

ResQueueHandler::ResQueueHandler(QObject *parent, PacketHandler *packHandler)
    : QObject(parent),packetHandler(packHandler)
{

    monitorServTimer.setInterval(30);
    monitorServTimer.start();
    connect(&monitorServTimer,SIGNAL(timeout()),this,SLOT(monitoringServant()));
}

ResQueueHandler::~ResQueueHandler()
{

}

void ResQueueHandler::handlRequests()
{

}

void ResQueueHandler::startPacketMonitor()
{
    //monitorPacket=new std::thread(monitoringServant);
    //monitorPacket.join();
}

void ResQueueHandler::monitoringServant()
{

    //collect packet which need handling;
    while(true)
    {
       for(auto &cl:allClients)
       {
          if(cl->getRequestCacheCounter()>0){
              allRequests[cl].push_back(cl->popRequestCache());
          }

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

void ResQueueHandler::sendFreshperoid()
{
    for(auto &cl:allClients)
    {
      cl->sendFreshPeriod();
    }
}

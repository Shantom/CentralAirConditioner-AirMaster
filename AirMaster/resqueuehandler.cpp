#include "resqueuehandler.h"

ResQueueHandler::ResQueueHandler(QObject *parent, PacketHandler *packHandler)
    : QObject(parent),packetHandler(packHandler),workingCounter(0)
{

    monitorServTimer.setInterval(30);
    monitorServTimer.start();
    connect(&monitorServTimer,SIGNAL(timeout()),this,SLOT(monitoringServant()));
}

ResQueueHandler::~ResQueueHandler()
{

}

void ResQueueHandler::handlWindRequests()
{
    for (auto &cl: allClients){
        if (allRequests[cl].size()>0){
            if (allRequests[cl].front()->getType() == START_WIND_PACKET){
                if (workingCounter < limitWorkingNum){
                    std::string velo = reinterpret_cast<StartWindClient*>(allRequests[cl].front())->velocity;
                    cl->sendWind(velo.c_str());
                    //                   qDebug()<<velo.c_str();
                    workingCounter++;

                    // update servant status
                    allServantsStatus[cl]->onLine = true;
                    allServantsStatus[cl]->velocity = true;
                    allRequests[cl].pop_front();
                }
            }
            else{
                cl->sendWind("NONE");
                allServantsStatus[cl]->onLine = false;
                if (workingCounter > 0){
                    workingCounter--;
                }
                allRequests[cl].pop_front();
            }
        }
    }
}

void ResQueueHandler::startPacketMonitor()
{
    //monitorPacket=new std::thread(monitoringServant);
    //monitorPacket.join();
}

void ResQueueHandler::monitoringServant()
{ 
    //collect packet which need handling
    for(auto &cl:allClients)
    {
        if(cl->getRequestCacheCounter()>0){
            AirPacket* rece = cl->popRequestCache();

            // get temperature packet and set current temperature
            if (rece->getType() == TEMP_PACKET){
                if (!servantIsFirstTemp[cl]){
                    cl->sendFreshPeriod();
                    servantIsFirstTemp[cl] =true;
                }
                else{
                    allServantsStatus[cl]->currentTemperature = reinterpret_cast<TemperatureClient*>(rece)->temp;
                }
            }
            // get room,id for this tcp pipe, and set its status onLine
            else if (rece->getType() == AUTH_PACKET){
                allServantsStatus[cl]->room = reinterpret_cast<AuthClient*>(rece)->room;
                allServantsStatus[cl]->id = reinterpret_cast<AuthClient*>(rece)->id;
                allServantsStatus[cl]->onLine = true;
                cl->sendWorkingState();
            }
            // collecting wind requests
            else{
                allRequests[cl].push_back(rece);
            }
        }
    }
    handlWindRequests();
}

PacketHandler *ResQueueHandler::getPacketHandler() const
{
    return packetHandler;
}

void ResQueueHandler::initQueueHandler()
{

}

void ResQueueHandler::addTcpServant(TcpPipeToServant *servant)
{
    allClients.push_back(servant);
    servant->setPacketHandler(packetHandler);

    // set servant status when connect to this servant
    allServantsStatus[servant] = new ServantStatus(true,false, fakeTemperature);
}

void ResQueueHandler::sendFreshperoid()
{
    for(auto &cl:allClients)
    {
        cl->sendFreshPeriod();
    }
}

//int ResQueueHandler::fakeTemperature = -999;

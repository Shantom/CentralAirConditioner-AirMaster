#include "resqueuehandler.h"

ResQueueHandler::ResQueueHandler(QObject *parent, PacketHandler *packHandler)
    : QObject(parent),packetHandler(packHandler),workingCounter(0)
{

    airReportor = new AiReportSystem();
    airFeer = new AirFee();


    // monitor servants and handle requests
    monitorServTimer.setInterval(30);
    monitorServTimer.start();
    connect(&monitorServTimer,SIGNAL(timeout()),this,SLOT(monitoringServant()));

    // count fee and send fee packet
    countFeeTimer.setInterval(300);
    countFeeTimer.start();
    connect(&countFeeTimer,SIGNAL(timeout()),this,SLOT(countingFee()));

}

ResQueueHandler::~ResQueueHandler()
{

}

void ResQueueHandler::handlWindRequests()
{
    // qDebug()<<" handling ........";
    for (auto &cl: allClients){
        if (allRequests[cl].size()>0){
            if (allRequests[cl].front()->getType() == START_WIND_PACKET){
                if (workingCounter < limitWorkingNum){
                    std::string velo = reinterpret_cast<StartWindClient*>(allRequests[cl].front())->velocity;
                    cl->sendWind(velo.c_str());
                    allServantsStatus[cl]->velocity = velo;


                    // report system and count fee
                    if (allServantsStatus[cl]->working){
                        updateRequestInfoStop(cl);
                    }
                    addRequestInfoStart(cl);


                    // update servant status
                    if (!allServantsStatus[cl]->working){
                        workingCounter++;
                        allServantsStatus[cl]->working = true;
                    }

                    allRequests[cl].pop_front();
                }
            }
            else{
                updateRequestInfoStop(cl);

                cl->sendWind("NONE");
                if (allServantsStatus[cl]->working){
                    workingCounter--;
                    allServantsStatus[cl]->working = false;
                }

                allRequests[cl].pop_front();
            }
        }
    }
}

//void ResQueueHandler::startPacketMonitor()
//{
//monitorPacket=new std::thread(monitoringServant);
//monitorPacket.join();
//}

void ResQueueHandler::monitoringServant()
{ 
    //collect packet which need handling
    for(TcpPipeToServant* &cl:allClients)
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
                    allServantsStatus[cl]->currentTemperature =
                            reinterpret_cast<TemperatureClient*>(rece)->temp;
                }
                qDebug()<<" get a temperature:    "<<rece->toJsonStr().c_str();
            }
            // get room,id for this tcp pipe, and set its status onLine
            else if (rece->getType() == AUTH_PACKET){
                allServantsStatus[cl]->room = reinterpret_cast<AuthClient*>(rece)->room;
                allServantsStatus[cl]->id = reinterpret_cast<AuthClient*>(rece)->id;
                allServantsStatus[cl]->onLine = true;
                cl->sendWorkingState();
                qDebug()<<" get a auth:    "<<rece->toJsonStr().c_str();
            }
            // collecting wind requests
            else{
                qDebug()<<" get a request:    "<<rece->toJsonStr().c_str();
                allRequests[cl].push_back(rece);
            }
        }
    }
    handlWindRequests();
}

void ResQueueHandler::countingFee()
{
    float kwhCounter = 0.5;
    for (auto& cl:allClients){
        if(allServantsStatus[cl]->onLine){
            if (allServantsStatus[cl]->velocity == "HIGH"){
                kwhCounter *=3;
            }
            else if(allServantsStatus[cl]->velocity == "LOW"){
                kwhCounter *=1;
            }
            else{
                kwhCounter *=2;
            }
            float feeTemp = airFeer->getFeeUnit()*kwhCounter;
            airFeer->updateFeePower(allServantsStatus[cl]->room,feeTemp,kwhCounter);
            cl->sendFee(feeTemp,kwhCounter);
        }
    }
}

std::string ResQueueHandler::currentTimeStamp()
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), "%d-%m-%Y %H-%M-%S");
    std::string nowTime = oss.str();
    return nowTime;
}

void ResQueueHandler::updateRequestInfoStop(TcpPipeToServant *cl)
{
    std::string roomId = allServantsStatus[cl]->room;

    // update last uncomplete RequestInfo
    pRequestInfo lastRequestInfo = airReportor->getRoomRequestInfo(roomId);
    if(lastRequestInfo)
    {
        lastRequestInfo->complete = true;
        lastRequestInfo->end_temperature = allServantsStatus[cl]->currentTemperature;
        lastRequestInfo->end_time = currentTimeStamp();
        airReportor->updateRequestComplete(lastRequestInfo);
    }
}

void ResQueueHandler::addRequestInfoStart(TcpPipeToServant* cl)
{

    // generate a new uncomplete RequestInfo
    pRequestInfo newInfo = new RequestInfo();
    newInfo->complete = false;
    newInfo->roomId = allServantsStatus[cl]->room ;
    newInfo->start_temperature = allServantsStatus[cl]->currentTemperature;
    newInfo->start_time = currentTimeStamp();
    newInfo->velocity = allServantsStatus[cl]->velocity;

    airReportor->addNewRequestInfo(newInfo);

}

PacketHandler *ResQueueHandler::getPacketHandler() const
{
    return packetHandler;
}

//void ResQueueHandler::initQueueHandler()
//{

//}

void ResQueueHandler::addTcpServant(TcpPipeToServant *servant)
{
    allClients.push_back(servant);
    servant->setPacketHandler(packetHandler);

    // set servant status when connect to this servant
    allServantsStatus[servant] = new ServantStatus(true,false, fakeTemperature,false);
}

void ResQueueHandler::sendFreshperoid()
{
    for(auto &cl:allClients)
    {
        cl->sendFreshPeriod();
    }
}

void ResQueueHandler::sendMode()
{
    for(auto cl:allClients)
    {
        cl->sendWorkingState();
    }

}

//int ResQueueHandler::fakeTemperature = -999;

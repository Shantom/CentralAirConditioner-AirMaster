#ifndef RESQUEUEHANDLER_H
#define RESQUEUEHANDLER_H

#include "tcppipetoservant.h"
#include "packethandler.h"
#include <thread>
#include <map>

class ResQueueHandler
{
public:
    ResQueueHandler(PacketHandler* packHandler);

    void handlRequests();
    void startPacketMonitor();
    void monitoringServant();
    void initQueueHandler();
    void addTcpServant(TcpPipeToServant* servant);
private:
    std::vector<TcpPipeToServant*> allClients;
    std::vector<TcpPipeToServant*> allHandling;
    std::map<TcpPipeToServant*,std::vector<AirPacket*>> allRequests;

    PacketHandler* packetHandler;
    std::thread monitorPacket;
};

#endif // RESQUEUEHANDLER_H

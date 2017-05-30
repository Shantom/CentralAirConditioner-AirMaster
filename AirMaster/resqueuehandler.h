#ifndef RESQUEUEHANDLER_H
#define RESQUEUEHANDLER_H

#include "tcppipetoservant.h"
#include "packethandler.h"
#include <thread>

class ResQueueHandler
{
public:
    ResQueueHandler(PacketHandler* packHandler);
    void startPacketMonitor();
    void monitoringServant();
    void initQueueHandler();
    void addTcpServant(TcpPipeToServant* servant);
private:
    std::vector<TcpPipeToServant*> allClients;
    std::vector<TcpPipeToServant*> allHandling;
    PacketHandler* packetHandler;
    std::thread monitorPacket;
};

#endif // RESQUEUEHANDLER_H

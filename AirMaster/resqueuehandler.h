#ifndef RESQUEUEHANDLER_H
#define RESQUEUEHANDLER_H

#include <thread>
#include <QTimer>
#include <QObject>
#include <map>
#include "tcppipetoservant.h"
#include "packethandler.h"


class ResQueueHandler: public QObject
{
   Q_OBJECT

public:
    explicit ResQueueHandler(QObject *parent = nullptr,PacketHandler* packHandler=nullptr);

    ~ResQueueHandler();
    void handlRequests();
    void startPacketMonitor();
    void initQueueHandler();
    void addTcpServant(TcpPipeToServant* servant);
    void sendFreshperoid();
signals:

public slots:
    void monitoringServant();
private:
    // all clients
    std::vector<TcpPipeToServant*> allClients;

    std::vector<TcpPipeToServant*> allHandling;


    // all requests at here
    std::map<TcpPipeToServant*,std::vector<AirPacket*>> allRequests;

    PacketHandler* packetHandler;
    std::thread monitorPacket;
    QTimer monitorServTimer;
};

#endif // RESQUEUEHANDLER_H

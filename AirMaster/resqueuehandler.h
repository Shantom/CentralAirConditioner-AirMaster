#ifndef RESQUEUEHANDLER_H
#define RESQUEUEHANDLER_H

#include <thread>
#include <QTimer>
#include <QObject>
#include <map>
#include <list>
#include "tcppipetoservant.h"
#include "packethandler.h"


typedef struct ServantStatus{
    bool open;
    bool onLine;
    int currentTemperature;
    std::string room;
    std::string id;
    ServantStatus(bool _open,bool _onLine,int temp):open(_open),onLine(_onLine),currentTemperature(temp){

    }
}ServantStatus , *pServantStatus;


class ResQueueHandler: public QObject
{
   Q_OBJECT

    static const int fakeTemperature = -999;
    static const int limitWorkingNum = 3;
public:
    explicit ResQueueHandler(QObject *parent = nullptr,PacketHandler* packHandler=nullptr);

    ~ResQueueHandler();
    void handlWindRequests();

    // monitoring servants and get new packets
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

    std::list<TcpPipeToServant*> allHandling;

    std::map<TcpPipeToServant*, pServantStatus> allServantsStatus;
    // all wind requests at here
    std::map<TcpPipeToServant*,std::list<AirPacket*>> allRequests;

    // count current servants given
    int workingCounter;
    PacketHandler* packetHandler;
    std::thread monitorPacket;
    QTimer monitorServTimer;
};

#endif // RESQUEUEHANDLER_H

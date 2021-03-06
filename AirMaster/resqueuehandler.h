#ifndef RESQUEUEHANDLER_H
#define RESQUEUEHANDLER_H

#include <thread>
#include <QTimer>
#include <QObject>
#include <map>
#include <list>
#include <algorithm>
#include "tcppipetoservant.h"
#include "aireportsystem.h"
#include "packethandler.h"
#include "aircommon.h"
#include "airfee.h"


typedef struct ServantStatus{
    bool open;
    bool onLine;
    int currentTemperature;
    std::string room;
    std::string id;
    std::string velocity;
    bool working;
    ServantStatus(bool _open,bool _onLine,int temp, bool _working)
        :open(_open),onLine(_onLine),currentTemperature(temp),working(_working){}
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
//    void startPacketMonitor();
//    void initQueueHandler();
    void addTcpServant(TcpPipeToServant* servant);
    void sendFreshperoid();
    void sendWorkingState();
    PacketHandler *getPacketHandler() const;
    std::map<TcpPipeToServant*, pServantStatus> getAllServantsStatus() const{return allServantsStatus;}

    AirFee *getAirFeer() const;

    AiReportSystem * getAirReportor()const{return airReportor;}


signals:

public slots:
    void monitoringServant();
    void countingFee();
private:
    // remove dead TcpPipeToServants
    void checkServants();
    // generate a timestamp
     std::string currentTimeStamp();

     // update RequestInfo in AiReportSystem when stop wind
     void updateRequestInfoStop(TcpPipeToServant* servant);

     // add new RequestInfo in AiReportSystem when start wind
     void addRequestInfoStart(TcpPipeToServant* servant);

    AiReportSystem * airReportor;
    AirFee * airFeer;

    // all clients
    std::vector<TcpPipeToServant*> allClients;

//    std::list<TcpPipeToServant*> allHandling;

    std::map<TcpPipeToServant*, pServantStatus> allServantsStatus;
    std::map<TcpPipeToServant*, bool> servantIsFirstTemp;
    // all wind requests at here
    std::map<TcpPipeToServant*,std::list<AirPacket*>> allRequests;

    // count current servants given
    int workingCounter;
    PacketHandler* packetHandler;
    std::thread monitorPacket;
    QTimer monitorServTimer;
    QTimer countFeeTimer;
};

#endif // RESQUEUEHANDLER_H

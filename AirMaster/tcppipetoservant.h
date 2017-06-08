#ifndef TCPPIPETOSERVANT_H
#define TCPPIPETOSERVANT_H

#include<QtNetwork>
#include <QObject>
#include <string>
#include <queue>
//#include <requeuehelper.h>
#include <packethandler.h>
#include "json.hpp"
using json=nlohmann::json;

class TcpPipeToServant : public QObject
{
    Q_OBJECT
public:
    explicit TcpPipeToServant(QObject *parent = nullptr,QTcpSocket* _clientTcp=nullptr);

    ~TcpPipeToServant();
//    void sendReplyPacket();
    void sendFreshPeriod();
    void sendWorkingState();
    void sendWind(std::string wind_velocity);
    void setClientTcp(QTcpSocket *value);
//  void examinePackHandler();

    void setPacketHandler(PacketHandler *value);

    void addRequestCache(AirPacket* res);
    AirPacket* popRequestCache();

    int getRequestCacheCounter() const;

signals:

public slots:
    void readPacket();
private:

    QTcpSocket* clientTcp;
    PacketHandler *packetHandler;
    std::string temperature;
    std::string ip;
    std::string port;

    std::queue<AirPacket*> requestCache;
    int requestCacheCounter;

};

#endif // TCPPIPETOSERVANT_H

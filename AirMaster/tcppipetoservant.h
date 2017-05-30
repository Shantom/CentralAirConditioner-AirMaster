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
    void sendFreshPeriod();
    void setClientTcp(QTcpSocket *value);
    void examinePackHandler();

    void setPacketHandler(PacketHandler *value);

    void addRequestCache(std::string res);
    std::string popRequestCache();

    int getRequestCacheCounter() const;

signals:

public slots:
    void readPacket();
private:

    QTcpSocket* clientTcp;
    PacketHandler *packetHandler;
    std::string ip;
    std::string port;

    std::queue<std::string> requestCache;
    int requestCacheCounter;

};

#endif // TCPPIPETOSERVANT_H

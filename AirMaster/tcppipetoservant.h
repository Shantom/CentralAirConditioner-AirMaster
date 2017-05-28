#ifndef TCPPIPETOSERVANT_H
#define TCPPIPETOSERVANT_H

#include<QtNetwork>
#include <QObject>
#include <packethandler.h>
#include "json.hpp"
using json=nlohmann::json;

class TcpPipeToServant : public QObject
{
    Q_OBJECT
public:
    explicit TcpPipeToServant(QObject *parent = nullptr,QTcpSocket* _clientTcp=nullptr,
                              PacketHandler* handler=nullptr);
    ~TcpPipeToServant();
    void setClientTcp(QTcpSocket *value);

signals:

public slots:
    void readPacket();
private:
    QTcpSocket* clientTcp;
    PacketHandler *packetHandler;

};

#endif // TCPPIPETOSERVANT_H

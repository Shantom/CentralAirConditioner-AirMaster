#ifndef REQUEUEHELPER_H
#define REQUEUEHELPER_H
#include<QtNetwork>
#include <QObject>
#include "tcppipetoservant.h"
#include "json.hpp"
using json=nlohmann::json;

class ReQueueHelper : public QObject
{
    Q_OBJECT
public:
    explicit ReQueueHelper(QObject *parent = nullptr);
    ~ReQueueHelper();
    void initQueueHelper();
    void startReceive();
    void initPacketHandler(AirConditionMaster& airmaster);
private:

    void receiveRequest();
    QTcpServer *receiveServer;
    std::vector<TcpPipeToServant*> allClients;
    PacketHandler* packHandler;
signals:


public slots:
 void acceptConnection();
};

#endif // REQUEUEHELPER_H

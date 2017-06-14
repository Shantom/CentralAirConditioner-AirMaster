#ifndef REQUEUEHELPER_H
#define REQUEUEHELPER_H
#include<QtNetwork>
#include <QObject>
#include <queue>
#include "tcppipetoservant.h"
#include "resqueuehandler.h"
#include "json.hpp"
using json=nlohmann::json;

class ReQueueHelper : public QObject
{
    Q_OBJECT
public:
    explicit ReQueueHelper(QObject *parent = nullptr,ResQueueHandler* resQueue=nullptr);
    ~ReQueueHelper();
    void initQueueHelper();
    void startReceive();
    void sendFreshPeroid();
    void sendWorkingState();
    void setResQueueHandler(ResQueueHandler *value);
    std::map<TcpPipeToServant*, pServantStatus> getAllServantsStatus() const
    {return resQueueHandler->getAllServantsStatus();}
    void sendMasterInfo();

    ResQueueHandler *getResQueueHandler() const;

private:

    void receiveRequest();
    QTcpServer *receiveServer;
    ResQueueHandler *resQueueHandler;
signals:


public slots:
 void acceptConnection();
};

#endif // REQUEUEHELPER_H

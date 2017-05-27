#ifndef RESQUEUEHELPER_H
#define RESQUEUEHELPER_H

#include<QtNetwork>
#include<vector>
class ResQueueHelper:QObject
{
public:
    ResQueueHelper();

    void startReceive();
private:
    void acceptConnection();
    void receiveRequest();
    QTcpServer *receiveServer;
    std::vector<QTcpSocket*> allClients;
};

#endif // RESQUEUEHELPER_H

#include "resqueuehelper.h"

ResQueueHelper::ResQueueHelper()
{
    receiveServer=new QTcpServer();
    receiveServer->listen(QHostAddress::Any,6666);
    connect(receiveServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

}

void ResQueueHelper::acceptConnection()
{
    QTcpSocket *clientConnection=receiveServer->nextPendingConnection();
    allClients.push_back(clientConnection);
    QString clientRes=clientConnection->readAll();

}

void ResQueueHelper::receiveRequest()
{

}

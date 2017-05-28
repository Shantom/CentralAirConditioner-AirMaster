#include "requeuehelper.h"

ReQueueHelper::ReQueueHelper(QObject *parent) : QObject(parent)
{
    receiveServer=new QTcpServer();
    receiveServer->listen(QHostAddress::Any,6666);
    qDebug()<<"binding  6666";
    connect(receiveServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void ReQueueHelper::startReceive()
{

}

void ReQueueHelper::acceptConnection()
{
    QTcpSocket *clientConnection=receiveServer->nextPendingConnection();
    TcpPipeToServant *clientPipe=new TcpPipeToServant(nullptr,clientConnection);
    allClients.push_back(clientPipe);
    qDebug()<<"new connection established";
   // QByteArray clientRes=clientConnection->readAll();
   // std::string clientR=clientRes.toStdString();
   // qDebug()<<clientR;
   // json preStr=json::parse(clientR);
   // qDebug()<<QString::fromStdString(clientR);
}

void ReQueueHelper::receiveRequest()
{

}

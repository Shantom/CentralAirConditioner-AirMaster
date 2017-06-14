#include "requeuehelper.h"

ReQueueHelper::ReQueueHelper(QObject *parent, ResQueueHandler *resQueue)
    : QObject(parent),resQueueHandler(resQueue)
{
    receiveServer=new QTcpServer();
    receiveServer->listen(QHostAddress::Any,6666);
    qDebug()<<"binding  6666";
    connect(receiveServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

ReQueueHelper::~ReQueueHelper()
{
    delete receiveServer;
}

void ReQueueHelper::initQueueHelper()
{

}

void ReQueueHelper::startReceive()
{

}

void ReQueueHelper::acceptConnection()
{
    QTcpSocket *clientConnection=receiveServer->nextPendingConnection();
    TcpPipeToServant *clientPipe=new TcpPipeToServant(nullptr,clientConnection);
    clientPipe->setPacketHandler(resQueueHandler->getPacketHandler());
    //clientPipe->sendFreshPeriod();//*
    resQueueHandler->addTcpServant(clientPipe);

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

void ReQueueHelper::setResQueueHandler(ResQueueHandler *value)
{
    resQueueHandler = value;
}

void ReQueueHelper::sendMasterInfo()
{
    resQueueHandler->sendFreshperoid();
    resQueueHandler->sendMode();

}

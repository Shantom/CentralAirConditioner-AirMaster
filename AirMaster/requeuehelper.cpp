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

void ReQueueHelper::sendFreshPeroid()
{
    resQueueHandler->sendFreshperoid();
}

void ReQueueHelper::sendWorkingState()
{
    resQueueHandler->sendWorkingState();
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

ResQueueHandler *ReQueueHelper::getResQueueHandler() const
{
    return resQueueHandler;
}

void ReQueueHelper::setResQueueHandler(ResQueueHandler *value)
{
    resQueueHandler = value;
}


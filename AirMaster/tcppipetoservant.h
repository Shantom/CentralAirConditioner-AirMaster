#ifndef TCPPIPETOSERVANT_H
#define TCPPIPETOSERVANT_H

#include<QtNetwork>
#include <QObject>
#include "json.hpp"
using json=nlohmann::json;

class TcpPipeToServant : public QObject
{
    Q_OBJECT
public:
    explicit TcpPipeToServant(QObject *parent = nullptr,QTcpSocket* _clientTcp=nullptr);

    void setClientTcp(QTcpSocket *value);

signals:

public slots:
    void readPacket();
private:
    QTcpSocket* clientTcp;
};

#endif // TCPPIPETOSERVANT_H

#include "ServerHandler.h"

ServerHandler::ServerHandler(QObject *parent)
    : QObject(parent)
{
    m_server = new QTcpServer(this);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnectionHandler()));
    m_server->listen(QHostAddress::Any, 10101);
}

void ServerHandler::newConnectionHandler()
{
    m_client = m_server->nextPendingConnection();
    DLG_THR << "New connection: " << m_client->peerAddress().toString();
    connect(m_client, SIGNAL(readyRead()), this, SLOT(readClientMessage()));
}

void ServerHandler::readClientMessage()
{
    QString revMessage = m_client->readAll();
    DLG_THR << "Client send: " << revMessage;
    QRegExp rx("(\\[|\\]|\\,)");
    QStringList elements = revMessage.split(rx);
    MODEL->setLat(elements.at(2).toDouble());
    MODEL->setLng(elements.at(5).toDouble());
    MODEL->setTemp(elements.at(8).toDouble());
    MODEL->setHumi(elements.at(11).toDouble());
}

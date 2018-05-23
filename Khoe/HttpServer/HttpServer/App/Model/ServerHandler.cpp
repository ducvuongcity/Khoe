#include "ServerHandler.h"

ServerHandler::ServerHandler(QObject *parent)
    : QObject(parent)
{
    MODEL;
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
    if(revMessage.startsWith("$[")){
        QRegExp rx("(\\[|\\]|\\,)");
        QStringList elements = revMessage.split(rx);
        if(elements.size() > 17) {
            MODEL->setLat(elements.at(2));
            MODEL->setLng(elements.at(5));
            MODEL->setTemp(elements.at(8));
            MODEL->setHumi(elements.at(11));
            MODEL->setRain(elements.at(14).toInt() == 0);
            MODEL->setDust(elements.at(17));
        }

        MODEL->addHistoryDataRow(QDateTime::currentDateTime().toString("HH:mm:ss dd-MM-yyyy")
                                 , MODEL->lat()
                                 , MODEL->lng()
                                 , MODEL->temp()
                                 , MODEL->humi()
                                 , MODEL->rain()
                                 , MODEL->dust());
    }
}

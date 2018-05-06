#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QRegExp>

#include "common.h"
#include "DataManager.h"

class ServerHandler : public QObject
{
    Q_OBJECT

public:
    explicit ServerHandler(QObject *parent = nullptr);

signals:

public slots:
    void newConnectionHandler();
    void readClientMessage();

private:
    QTcpServer *m_server = nullptr;
    QTcpSocket *m_client = nullptr;
};

class ServerHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerHandlerThread(QObject *parent = nullptr)
        : QThread(parent) {}
protected:
    void run() {
        ServerHandler handler;
        exec();
    }
};

#endif // SERVERHANDLER_H

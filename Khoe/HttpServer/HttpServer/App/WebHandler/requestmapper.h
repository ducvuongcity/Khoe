#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <QProcess>

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "mainpagecontroller.h"

#include "ServerHandler.h"

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0);
    ~RequestMapper();
    void service(HttpRequest& request, HttpResponse& response);
    static HttpSessionStore* sessionStore;

private:
    MainPageController mainPageController;
    ServerHandlerThread m_serverHandler;
};

#endif // REQUESTMAPPER_H

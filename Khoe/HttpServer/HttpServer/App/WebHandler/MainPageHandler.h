#ifndef MAINPAGEHANDLER
#define MAINPAGEHANDLER

#include "common.h"
#include "DataManager.h"
#include "httprequesthandler.h"


class MainPageHandler : public HttpRequestHandler
{
    Q_OBJECT

public:
    MainPageHandler(QObject* parent=0);
    ~MainPageHandler();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse&);

private:
    QString htmlPage;
};

#endif // MAINPAGEHANDLER


#ifndef MAINPAGECONTROLLER
#define MAINPAGECONTROLLER

#include "httprequesthandler.h"
#include "parameter.h"
#include <QProcess>

class MainPageController : public HttpRequestHandler {
    Q_OBJECT
public:
    MainPageController(QObject* parent=0);
    ~MainPageController();
    void service(HttpRequest& request, HttpResponse& response);
    void sendHTML(HttpResponse&);

private:
    QString htmlPage;
};

#endif // MAINPAGECONTROLLER


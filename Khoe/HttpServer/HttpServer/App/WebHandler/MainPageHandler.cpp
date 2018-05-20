#include "MainPageHandler.h"

MainPageHandler::MainPageHandler(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace(QString("\n"), QString(""));
}

MainPageHandler::~MainPageHandler()
{}

void MainPageHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    QString updateMsg;

    if(msgBody.contains("update")) {
        updateMsg = QString("msg_update,%1,%2,%3,%4,%5,%6")
                .arg(MODEL->lat())
                .arg(MODEL->lng())
                .arg(MODEL->temp())
                .arg(MODEL->humi())
                .arg(MODEL->rain())
                .arg(MODEL->dust());

        response.flush();
        response.write(QByteArray::fromStdString(updateMsg.toStdString()));
    }
    else {
        DLG << "Rev: " + msgBody;
    }
}

void MainPageHandler::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

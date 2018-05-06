#include <QTime>
#include <QDebug>
#include "mainpagecontroller.h"
#include "DataManager.h"

MainPageController::MainPageController(QObject *parent)
    :HttpRequestHandler(parent)
{
    QFile page(PATH_WEB);
    if (!page.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&page);
    in.setCodec("UTF-8");
    htmlPage = in.readAll().replace(QString("\n"), QString(""));
}

MainPageController::~MainPageController()
{}

void MainPageController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray msgBody = request.getBody();
    QString updateMsg;

    if(msgBody.contains("update")) {
        DLG_THR << "Request update";
        updateMsg = QString("msg_update,%1,%2,%3,%4")
                .arg(MODEL->lat())
                .arg(MODEL->lng())
                .arg(MODEL->temp())
                .arg(MODEL->humi());

        response.flush();
        response.write(QByteArray::fromStdString(updateMsg.toStdString()));
    }
    else {
        DLG << "Rev: " + msgBody;
    }

}

void MainPageController::sendHTML(HttpResponse &response)
{
    response.write(htmlPage.toUtf8());
}

#ifndef PARAMETER
#define PARAMETER

#include <QDebug>
#include <QThread>

#define DLOG_THREAD         qDebug()    << "[" << QThread::currentThreadId() << "][" \
                                        << Q_FUNC_INFO << "]"

#define DLG_THR             qDebug()    << "[" << QThread::currentThreadId() << "][" \
                                        << Q_FUNC_INFO << "]"

#define DLG                 qDebug()

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB            ":/web/resources/web/mainPage.html"

#define MODEL               DataManager::getInstance()

#define DEFAULT_LNG         QString("105.8431605")     //kinh độ
#define DEFAULT_LAT         QString("21.0065189")      //vĩ độ
#define DEFAULT_TEMP        QString("32")     //kinh độ
#define DEFAULT_HUMI        QString("84")      //vĩ độ

#define PH_DB               "E://Air/air.db"

#endif // PARAMETER


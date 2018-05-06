#ifndef PARAMETER
#define PARAMETER

#include <QDebug>
#include <QThread>

#define DLG_THR             qDebug()    << "[" << QThread::currentThreadId() << "][" \
                                        << Q_FUNC_INFO << "]"
#define DLG                 qDebug()

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB            ":/web/resources/web/mainPage.html"

#define MODEL               DataManager::getInstance()

#define DEFAULT_LNG         105     //kinh độ
#define DEFAULT_LAT         21      //vĩ độ

#endif // PARAMETER


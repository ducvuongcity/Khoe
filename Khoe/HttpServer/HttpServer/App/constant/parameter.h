#ifndef PARAMETER
#define PARAMETER

#include <QDebug>
#include <QThread>

#include "pivariables.h"

#define DLG_THR             qDebug() << "[" << QThread::currentThreadId() << "]"
#define DLG                 qDebug()

#define PATH_INI            ":/config/resources/config.ini"
#define PATH_WEB            ":/web/resources/web/mainPage.html"
#define PATH_WEB2           ":/web/resources/web/newPage.html"

#define TOKEN               QString(",")

#define MODEL               DataManager::getInstance()

#endif // PARAMETER


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

enum AlertTemperature{
    TEMP_NORMAL,
    TEMP_LOW,
    TEMP_HIGH
};

enum AlertHumidity{
    HUMI_NORMAL,
    HUMI_LOW,
    HUMI_HIGH
};

enum AlertRain {
    RAIN_NO_RAIN,
    RAIN_RAINING
};

enum AlertDust {
    DUST_LV1_EXCELLENT,
    DUST_LV2_AVERAGE,
    DUST_LV3_LIGHT_POLLUTION,
    DUST_LV4_MODERATE_POLLUTION,
    DUST_LV5_HEAVY_POLLUTION,
    DUST_LV6_SERIOUS_POLLUTION
};

#endif // PARAMETER


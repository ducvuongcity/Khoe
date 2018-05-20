#include "DataManager.h"

DataManager *DataManager::m_instance = nullptr;

DataManager::DataManager(QObject *parent)
    : QObject(parent)
    , m_lat(DEFAULT_LAT)
    , m_lng(DEFAULT_LNG)
    , m_temp(DEFAULT_TEMP)
    , m_humi(DEFAULT_HUMI)
    , m_rain(false)
    , m_dust("0")
{
    createDatabase();
    initDb();
}

DataManager* DataManager::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new DataManager();
    return m_instance;
}

QString DataManager::temp() const
{
    return m_temp;
}

void DataManager::setTemp(const QString &temp)
{
    if(m_temp != temp)
        m_temp = temp;
}

QString DataManager::humi() const
{
    return m_humi;
}

void DataManager::setHumi(const QString &humi)
{
    if(m_humi != humi)
        m_humi = humi;
}

QString DataManager::lat() const
{
    return m_lat;
}

void DataManager::setLat(const QString &lat)
{
    if(m_lat != lat)
        m_lat = lat;
}

QString DataManager::lng() const
{
    return m_lng;
}

void DataManager::setLng(const QString &lng)
{
    if(m_lng != lng)
        m_lng = lng;
}

QString DataManager::dust() const
{
    return m_dust;
}

void DataManager::setDust(const QString &dust)
{
    if(m_dust != dust)
        m_dust = dust;
}

bool DataManager::rain() const
{
    return m_rain;
}

void DataManager::setRain(bool rain)
{
    if(m_rain != rain)
        m_rain = rain;
}

bool DataManager::createDatabase()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        DLOG_THREAD << "Unable to load database, needs install SQLITE driver";
    }
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    bool success = false;
    database.setDatabaseName(PH_DB);
    if (database.open()) {
        DLOG_THREAD << "Database created/registered.";
        success = true;
    } else {
        DLOG_THREAD << "Error opening connection to the database: " << database.lastError().text();
    }
    database.close();
    return success;
}

void DataManager::initDb()
{
    if(isDbExists()) {
        QSqlDatabase database = QSqlDatabase::database();
        if (!database.tables().contains("HistoryData")) {
            createHistoryDataTable();
        }
    }
}

bool DataManager::isDbExists()
{
    return QFile::exists(PH_DB);
}

void DataManager::createHistoryDataTable()
{
    QSqlDatabase database = QSqlDatabase::database();
    const QString createSQL = "CREATE TABLE IF NOT EXISTS HistoryData("
                              "time DATETIME NOT NULL,"
                              "lat TEXT,"
                              "lng TEXT,"
                              "temp TEXT,"
                              "humi TEXT,"
                              "rain BOOLEAN,"
                              "dust TEXT);";
    QSqlQuery query(database);
    if (query.exec(createSQL)) {
        DLOG_THREAD << "Table creation query execute successfully";
    } else {
        DLOG_THREAD << "Create table error: " << database.lastError().text();
    }
    database.close();
}

void DataManager::addHistoryDataRow(QString time, QString lat, QString lng, QString temp, QString humi, bool rain, QString dust)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("HistoryData")) {
        DLOG_THREAD << "Create record error: Accounts table does not exist.";
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO HistoryData(time, lat, lng, temp, humi, rain, dust) "
                      "VALUES (:time, :lat, :lng, :temp, :humi, :rain, :dust);");
        query.bindValue(":time", time);
        query.bindValue(":lat", lat);
        query.bindValue(":lng", lng);
        query.bindValue(":temp", temp);
        query.bindValue(":humi", humi);
        query.bindValue(":rain", rain);
        query.bindValue(":dust", dust);
        if (query.exec()) {
            DLOG_THREAD <<  "Insert done";
        } else {
            DLOG_THREAD << "Insert error: " << database.lastError().text();
        }
    }
    database.close();
}


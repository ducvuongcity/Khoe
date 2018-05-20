#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlError>
#include <QFile>

#define DB_PATH "air.db"

#include "common.h"

class DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);
    static DataManager* getInstance();

    QString temp() const;
    void setTemp(const QString &temp);

    QString humi() const;
    void setHumi(const QString &humi);

    QString lat() const;
    void setLat(const QString &lat);

    QString lng() const;
    void setLng(const QString &lng);

    QString dust() const;
    void setDust(const QString &dust);

    bool rain() const;
    void setRain(bool rain);

    bool createDatabase();
        void initDb();
        bool isDbExists();
        void createHistoryDataTable();
        void addHistoryDataRow(QString time,
                               QString lat,
                               QString lng,
                               QString temp,
                               QString humi,
                               bool rain,
                               QString dust);

private:
    static DataManager* m_instance;

    QString m_lat;
    QString m_lng;
    QString m_temp;
    QString m_humi;
    bool m_rain;
    QString m_dust;
};

#endif // DATAMANAGER_H

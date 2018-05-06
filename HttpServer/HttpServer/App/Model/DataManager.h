#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    static DataManager* getInstance();

    double temp() const;
    void setTemp(double temp);

    double humi() const;
    void setHumi(double humi);

    double lat() const;
    void setLat(double lat);

    double lng() const;
    void setLng(double lng);

private:
    static DataManager* m_instance;

    double m_temp;
    double m_humi;
    double m_lat;
    double m_lng;
};

#endif // DATAMANAGER_H

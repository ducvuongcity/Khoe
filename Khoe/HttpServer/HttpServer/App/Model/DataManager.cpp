#include "DataManager.h"

DataManager *DataManager::m_instance = nullptr;

DataManager::DataManager(QObject *parent)
    : QObject(parent)
    , m_temp(DEFAULT_TEMP)
    , m_humi(DEFAULT_HUMI)
    , m_lat(DEFAULT_LAT)
    , m_lng(DEFAULT_LNG)
{}

DataManager* DataManager::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new DataManager();
    return m_instance;
}

double DataManager::temp() const
{
    return m_temp;
}

void DataManager::setTemp(double temp)
{
    if(m_temp != temp)
        m_temp = temp;
}

double DataManager::humi() const
{
    return m_humi;
}

void DataManager::setHumi(double humi)
{
    if(m_humi != humi)
        m_humi = humi;
}

double DataManager::lat() const
{
    return m_lat;
}

void DataManager::setLat(double lat)
{
    if(m_lat != lat)
        m_lat = lat;
}

double DataManager::lng() const
{
    return m_lng;
}

void DataManager::setLng(double lng)
{
    if(m_lng != lng)
        m_lng = lng;
}


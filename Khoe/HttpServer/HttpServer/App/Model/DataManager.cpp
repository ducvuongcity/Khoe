#include "DataManager.h"

DataManager *DataManager::m_instance = nullptr;

DataManager::DataManager(QObject *parent)
    : QObject(parent)
    , m_lat(0)
    , m_lng(0)
    , m_temp(0)
    , m_humi(0)
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
    m_temp = temp;
}

double DataManager::humi() const
{
    return m_humi;
}

void DataManager::setHumi(double humi)
{
    m_humi = humi;
}

double DataManager::lat() const
{
    return m_lat;
}

void DataManager::setLat(double lat)
{
    m_lat = lat;
}

double DataManager::lng() const
{
    return m_lng;
}

void DataManager::setLng(double lng)
{
    m_lng = lng;
}


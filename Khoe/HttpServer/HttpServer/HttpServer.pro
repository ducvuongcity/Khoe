QT  += core
QT  -= gui
QT  += network
QT  += serialport

TARGET = HttpServer

TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += \
    $$PWD/../QtWebApp/httpserver/ \
    $$PWD/App \
    $$PWD/App/constant \
    $$PWD/App/WebHandler \
    $$PWD/App/Model

SOURCES += \
    App/main.cpp \
    App/WebHandler/RequestMapper.cpp \
    App/WebHandler/MainPageHandler.cpp \
    App/Model/DataManager.cpp \
    App/Model/ServerHandler.cpp

HEADERS += \
    App/WebHandler/RequestMapper.h \
    App/WebHandler/MainPageHandler.h \
    App/constant/common.h \
    App/Model/DataManager.h \
    App/Model/ServerHandler.h

OTHER_FILES +=

include(../QtWebApp/httpserver/httpserver.pri)

RESOURCES += \
    ini.qrc
